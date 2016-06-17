import sys
import glob
import serial
import time
import binascii

def serial_ports():
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result


def read_serial():
        try:
            while True:
                user_out = raw_input("Enter what you want to send:")
                print "Sending: "+  user_out.decode("hex")
                #ser.write(' '.join(format(x, 'b') for x in bytearray(user_out.decode("hex"))))
                ser.write( user_out.decode("hex"))
                time.sleep(1)

                while ser.inWaiting() > 0:
                    # ser.flushInput()
                    device_output = binascii.hexlify(ser.read(ser.inWaiting()))
                    print "Response: "+ device_output
                    # if (device_output=="0100410aa3a51000efff"):
                    #     print "Bootrom version: "+ str(int(device_output[:8],16))
                    ser.flushInput()

        except KeyboardInterrupt:
            ser.close()
            print "Done..."
            exit()


def convert_to_ihex():
    print "This function converts .axf to .ihex using arm-none-eabi-objcopy"


if __name__ == '__main__':
    # print "Your serial port :",sys.argv[1]

    for i in range(0,len(serial_ports())):
        print str(i)+": "+serial_ports()[i]

    user_port= input("Enter the port on which your board is connected: ")
    print "Opening port : " + serial_ports()[int(user_port)]


    ser = serial.Serial(
    port = str(serial_ports()[int(user_port)]),
    baudrate = 115200
    )
    # ser.open()
    ser.flushInput()
    ser.flushOutput()
    read_serial()
    ser.close()
