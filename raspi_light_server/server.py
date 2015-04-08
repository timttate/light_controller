
from flask import Flask, request
from flask.ext.script import Manager
import serial

app = Flask(__name__)
manager = Manager(app)

SERIAL_PORT = "/dev/cu.usbmodemfd121"

@app.route("/")
def index():
    return "hello world!"

@app.route("/on")
def turn_on():
    serial_command = "set_state on"
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return serial_command

@app.route("/off")
def turn_off():
    serial_command = "set_state off"
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()
    return "turned off"

@app.route("/set_rgb", methods=["GET"])
def set_rgb():
    red = int(request.args.get('red', '0'))
    green = int(request.args.get('green', '0'))
    blue = int(request.args.get('blue', '0'))

    serial_command = "set_rgb %r %r %r" % (red, green, blue)
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return serial_command

@app.route("/set_bright", methods=["GET"])
def set_bright():
    brightness = int(request.args.get('brightness'))

    serial_command = "set_bright %r" % brightness
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return serial_command


if __name__ == "__main__":
    manager.run()
