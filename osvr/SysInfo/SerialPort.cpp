/** @file
    @brief Implementation

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/


// Internal Includes
#include <osvr/SysInfo/SerialPort.h>

// Library/third-party includes
#include <boost/bind.hpp>

// Standard includes
#include <algorithm>
#include <iostream>
#include <string>

namespace osvr {
namespace sysinfo {

using serial_port = boost::asio::serial_port_base;

SerialPort::SerialPort() : io_(), port_(io_), timer_(io_), timeout_(boost::posix_time::seconds(0))
{
    // do nothing
}

SerialPort::SerialPort(const std::string& device, unsigned int baud_rate, serial_port::parity parity, serial_port::character_size char_size, serial_port::flow_control flow_control, serial_port::stop_bits stop_bits) : io_(), port_(io_), timer_(io_), timeout_(boost::posix_time::seconds(0))
{
    open(device, baud_rate, parity, char_size, flow_control, stop_bits);
}

void SerialPort::open(const std::string& device, unsigned int baud_rate, serial_port::parity parity, serial_port::character_size char_size, serial_port::flow_control flow_control, serial_port::stop_bits stop_bits)
{
    if (isOpen())
        close();

    port_.open(device);
    port_.set_option(serial_port::baud_rate(baud_rate));
    port_.set_option(parity);
    port_.set_option(serial_port::character_size(char_size));
    port_.set_option(flow_control);
    port_.set_option(stop_bits);
}

bool SerialPort::isOpen() const
{
    return port_.is_open();
}

void SerialPort::close()
{
    if (!isOpen())
        return;

    port_.close();
}

void SerialPort::setTimeout(const boost::posix_time::time_duration& timeout)
{
    timeout_ = timeout;
}

void SerialPort::write(const char* data, size_t size)
{
    boost::asio::write(port_, boost::asio::buffer(data,size));
}

void SerialPort::write(const std::vector<char>& data)
{
    boost::asio::write(port_, boost::asio::buffer(&data[0], data.size()));
}

void SerialPort::write(const std::string& s)
{
    boost::asio::write(port_, boost::asio::buffer(s.c_str(), s.size()));
}

void SerialPort::writeLine(const std::string& data)
{
    write(data + "\n");
}

void SerialPort::read(char* data, size_t size)
{
    if (readData_.size()>0) {
        // If there is some data from a previous read
        std::istream is(&readData_);
        size_t toRead = std::min(readData_.size(), size); //How many bytes to read?
        is.read(data, toRead);
        data += toRead;
        size -= toRead;
        // If read data was enough, just return
        if (size == 0)
            return;
    }

    setupParameters_ = ReadSetupParameters(data, size);
    performReadSetup(setupParameters_);

    // For this code to work, there should always be a timeout, so the
    // request for no timeout is translated into a very long timeout
    if (timeout_ != boost::posix_time::seconds(0)) {
        timer_.expires_from_now(timeout_);
    } else {
        timer_.expires_from_now(boost::posix_time::hours(100000));
    }

    timer_.async_wait(boost::bind(&SerialPort::timeoutExpired, this, boost::asio::placeholders::error));

    result_ = ReadResult::InProgress;
    bytesTransferred_ = 0;
    while (true) {
        io_.run_one();

        switch(result_) {
        case ReadResult::Success:
            timer_.cancel();
            return;
        case ReadResult::TimeoutExpired:
            port_.cancel();
            throw timeout_exception("Timeout expired");
        case ReadResult::Error:
            timer_.cancel();
            port_.cancel();
            throw boost::system::system_error(boost::system::error_code(), "Error while reading");
        case ReadResult::InProgress:
            // keep looping
            continue;
        }
    }
}

std::vector<char> SerialPort::read(size_t size)
{
    std::vector<char> result(size, '\0'); // Allocate a vector with the desired size
    read(&result[0], size); // Fill it with values
    return result;
}

std::string SerialPort::readString(size_t size)
{
    std::string result(size, '\0'); // Allocate a string with the desired size
    read(&result[0], size); // Fill it with values
    return result;
}

std::string SerialPort::readStringUntil(const std::string& delim)
{
    // Note: if readData_ contains some previously read data, the call to
    // async_read_until (which is done in performReadSetup) correctly handles
    // it. If the data is enough it will also immediately call readCompleted()
    setupParameters_ = ReadSetupParameters(delim);
    performReadSetup(setupParameters_);

    // For this code to work, there should always be a timeout, so the
    // request for no timeout is translated into a very long timeout
    if (timeout_ != boost::posix_time::seconds(0)) {
        timer_.expires_from_now(timeout_);
    } else {
        timer_.expires_from_now(boost::posix_time::hours(100000));
    }

    timer_.async_wait(boost::bind(&SerialPort::timeoutExpired, this, boost::asio::placeholders::error));

    result_ = ReadResult::InProgress;
    bytesTransferred_ = 0;
    while (true) {
        io_.run_one();
        switch(result_) {
        case ReadResult::Success:
            {
                timer_.cancel();
                bytesTransferred_ -= delim.size(); // Don't count delim
                std::istream is(&readData_);
                std::string result(bytesTransferred_, '\0'); // Alloc string
                is.read(&result[0],bytesTransferred_); // Fill values
                is.ignore(delim.size()); // Remove delimiter from stream
                return result;
            }
        case ReadResult::TimeoutExpired:
            port_.cancel();
            throw timeout_exception("Timeout expired");
        case ReadResult::Error:
            timer_.cancel();
            port_.cancel();
            throw boost::system::system_error(boost::system::error_code(), "Error while reading");
        case ReadResult::InProgress:
            // keep looping
            continue;
        }
    }
}

SerialPort::~SerialPort()
{
    // do nothing
}

void SerialPort::performReadSetup(const ReadSetupParameters& param)
{
    if (param.fixedSize) {
        boost::asio::async_read(port_, boost::asio::buffer(param.data, param.size), boost::bind(
                &SerialPort::readCompleted, this, boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
    } else {
        boost::asio::async_read_until(port_, readData_, param.delim, boost::bind(
                &SerialPort::readCompleted, this, boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
    }
}

void SerialPort::timeoutExpired(const boost::system::error_code& error)
{
     if (!error && result_ == ReadResult::InProgress)
         result_ = ReadResult::TimeoutExpired;
}

void SerialPort::readCompleted(const boost::system::error_code& error, const size_t bytes_transferred)
{
    if (!error) {
        result_ = ReadResult::Success;
        bytesTransferred_ = bytes_transferred;
        return;
    }

    // In case a asynchronous operation is cancelled due to a timeout,
    // each OS seems to have its way to react.
#ifdef OSVR_WINDOWS
    if (error.value() == 995)
        return; // Windows spits out error 995
#elif OSVR_MACOSX
    if (error.value() == 45) {
        // Bug on OS X, it might be necessary to repeat the setup
        // http://osdir.com/ml/lib.boost.asio.user/2008-08/msg00004.html
        performReadSetup(setupParameters_);
        return;
    }
#else // Linux (and everything else)
    if (error.value() == 125)
        return; // Linux outputs error 125
#endif

    result_ = ReadResult::Error;
}

} // namespace sysinfo
} // namespace osvr

