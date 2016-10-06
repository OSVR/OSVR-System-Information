/** @file
    @brief Header

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Based on code written by Terraneo Federico and licensed under the
// Boost Software License, Version 1.0.
//
// <http://www.webalice.it/fede.tft/serial_port/serial_port.html>

#ifndef INCLUDED_SerialPort_h_GUID_9FE8443E_6A14_47A0_B2B0_95113A62D733
#define INCLUDED_SerialPort_h_GUID_9FE8443E_6A14_47A0_B2B0_95113A62D733

// Internal Includes
// - none

// Library/third-party includes
#include <osvr/Util/PlatformConfig.h>
#ifdef OSVR_WINDOWS
#include <SDKDDKVer.h>>
#endif
#include <boost/asio.hpp>
#include <boost/utility.hpp>

// Standard includes
#include <stdexcept>
#include <string>
#include <vector>

namespace osvr {
namespace sysinfo {

/**
 * Thrown if timeout occurs
 */
class timeout_exception : public std::runtime_error {
public:
    timeout_exception(const std::string& msg): runtime_error(msg)
    {
        // do nothing
    }
};

class SerialPort {
public:
    using serial_port = boost::asio::serial_port_base;

    /** SerialPort is noncopyable. */
    //@{
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    //@}

    SerialPort();

    /**
     * Opens a serial port. By default timeout is disabled.
     *
     * @param device device name (e.g., /dev/ttyS0 or COM1)
     * @param baud_rate baud rate
     * @param parity parity (default: none)
     * @param char_size character size in bits (default: 8 bits)
     * @param flow_control flow control (default: none)
     * @param stop_bits stop bits (default: 1)
     *
     * @throw boost::system::system_error if cannot open the serial device
     */
    SerialPort(const std::string& device, unsigned int baud_rate, serial_port::parity parity = serial_port::parity(serial_port::parity::none), serial_port::character_size char_size = serial_port::character_size(8), serial_port::flow_control flow_control = serial_port::flow_control(serial_port::flow_control::none), serial_port::stop_bits stop_bits = serial_port::stop_bits(serial_port::stop_bits::one));

    ~SerialPort();

    /**
     * Opens a serial device.
     *
     * @param device device name (e.g., /dev/ttyS0 or COM1)
     * @param baud_rate baud rate
     * @param parity parity (default: none)
     * @param char_size character size in bits (default: 8 bits)
     * @param flow_control flow control (default: none)
     * @param stop_bits stop bits (default: 1)
     *
     * @throw boost::system::system_error if cannot open the serial device
     */
    void open(const std::string& device, unsigned int baud_rate, serial_port::parity parity = serial_port::parity(serial_port::parity::none), serial_port::character_size char_size = serial_port::character_size(8), serial_port::flow_control flow_control = serial_port::flow_control(serial_port::flow_control::none), serial_port::stop_bits stop_bits = serial_port::stop_bits(serial_port::stop_bits::one));

    /**
     * @return true if serial port is open
     */
    bool isOpen() const;

    /**
     * Closes the serial port.
     *
     * @throw boost::system::system_error if any error
     */
    void close();

    /**
     * Set the timeout on read/write operations.
     * To disable the timeout, call setTimeout(boost::posix_time::seconds(0));
     */
    void setTimeout(const boost::posix_time::time_duration& timeout);

    /**
     * Write data to the serial port.
     *
     * @param data array of char to be sent through the serial device
     * @param size array size
     *
     * @throws boost::system::system_error if any error
     */
    //@{
    void write(const char* data, size_t size);
    void write(const std::vector<char>& data);
    void write(const std::string& data);
    void writeLine(const std::string& data);
    //@}

    /**
     * Read data from serial port.
     *
     * @param data array to fill with read data
     * @param size number of bytes of data to read
     *
     * @throws boost::system::system_error if any error
     * @throws timeout_exception in case of timeout
     */
    //@{
    void read(char* data, size_t size);
    std::vector<char> read(size_t size);
    //@}

    /**
     * Read string data from serial port.
     *
     * Can only be used if the serial device will not send binary data. For
     * binary data read, use @c read() instead.
     *
     * The returned string is empty if no data has arrived.
     *
     * @param size number of bytes of data to read
     *
     * @return a string with the received data.
     *
     * @throws boost::system::system_error if any error
     * @throws timeout_exception in case of timeout
     */
    std::string readString(size_t size);

    /**
     * Read a line, blocking.
     *
     * Can only be used if the user is sure that the serial device will not
     * send binary data. For binary data read, use @c read() instead.
     *
     * The returned string is empty if the line delimiter has not yet arrived.
     *
     * @param delimiter line delimiter (default: '\n')
     *
     * @return a string with the received data. The delimiter is removed from
     * the string.
     *
     * @throws boost::system::system_error if any error
     * @throws timeout_exception in case of timeout
     */
    std::string readStringUntil(const std::string& delim = "\n");

private:
    /**
     * Parameters of performReadSetup.
     * Just wrapper class, no encapsulation provided
     */
    class ReadSetupParameters {
    public:
        ReadSetupParameters(): fixedSize(false), delim(""), data(0), size(0)
        {
            // do nothing
        }

        explicit ReadSetupParameters(const std::string& delim) : fixedSize(false), delim(delim), data(0), size(0)
        {
            // do nothing
        }

        ReadSetupParameters(char* data, size_t size) : fixedSize(true), delim(""), data(data), size(size)
        {
            // do nothing
        }

        bool fixedSize;    ///< True if need to read a fixed number of parameters
        std::string delim; ///< String end delimiter (valid if fixedSize=false)
        char* data;        ///< Pointer to data array (valid if fixedSize=true)
        size_t size;       ///< Array size (valid if fixedSize=true)
    };

    /**
     * This member function sets up a read operation, both reading a specified
     * number of characters and reading until a delimiter string.
     */
    void performReadSetup(const ReadSetupParameters& param);

    /**
     * Callack called either when the read timeout is expired or canceled.
     * If called because timeout expired, sets result to resultTimeoutExpired
     */
    void timeoutExpired(const boost::system::error_code& error);

    /**
     * Callback called either if a read complete or read error occurs
     * If called because of read complete, sets result to resultSuccess
     * If called because read error, sets result to resultError
     */
    void readCompleted(const boost::system::error_code& error, const size_t bytes_transferred);

    /**
     * Possible outcome of a read. Set by callbacks, read from main code
     */
    enum class ReadResult {
        InProgress,
        Success,
        Error,
        TimeoutExpired
    };

    boost::asio::io_service io_;               ///< Io service object
    boost::asio::serial_port port_;            ///< Serial port object
    boost::asio::deadline_timer timer_;        ///< Timer for timeout
    boost::posix_time::time_duration timeout_; ///< Read/write timeout
    boost::asio::streambuf readData_;          ///< Holds eventual read but not consumed
    ReadResult result_;                        ///< Used by read with timeout
    size_t bytesTransferred_;                  ///< Used by async read callback
    ReadSetupParameters setupParameters_;      ///< Global because used in the OSX fix
};

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_SerialPort_h_GUID_9FE8443E_6A14_47A0_B2B0_95113A62D733

