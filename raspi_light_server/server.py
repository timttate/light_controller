
from flask import Flask, request, render_template
from flask.ext.script import Manager
import serial

app = Flask(__name__)
manager = Manager(app)

SERIAL_PORT = "/dev/cu.usbmodemfd121"

@app.route("/")
def index():
    return generate_remote()

@app.route("/on")
def turn_on():
    serial_command = "set_state on\n"
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return generate_remote(serial_command)

@app.route("/off")
def turn_off():
    serial_command = "set_state off\n"
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return generate_remote(serial_command)

@app.route("/set_rgb", methods=["GET"])
def set_rgb():
    red = int(request.args.get('red', '0'))
    green = int(request.args.get('green', '0'))
    blue = int(request.args.get('blue', '0'))

    serial_command = "set_rgb %r %r %r\n" % (red, green, blue)
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return generate_remote(serial_command)

@app.route("/set_bright", methods=["GET"])
def set_bright():
    brightness = int(request.args.get('brightness'))

    serial_command = "set_bright %r\n" % brightness
    ser = serial.Serial(SERIAL_PORT)
    ser.write(serial_command)
    ser.close()

    return generate_remote(serial_command)

class rgb:
    def __init__(self, red, green, blue):
        self.red = red
        self.green = green
        self.blue = blue

@app.route("/generate_remote")
def generate_remote(message=None):
    color_map = [
        [
            ("Red", rgb(255, 0, 0)),
            ("Green", rgb(0, 255, 0)),
            ("Blue", rgb(0, 0, 255)),
            ("White", rgb(255, 255, 255))
        ], [
            ("Red Orange", rgb(255, 64, 0)),
            ("<Bluish Green>", rgb(0, 255, 64)),
            ("Ultramarine", rgb(64, 0, 255)),
            ("3000K", rgb(255, 177, 110)),
        ], [
            ("Orange", rgb(255, 127, 0)),
            ("Spring Green", rgb(0, 255, 127)),
            ("Violet", rgb(127, 0, 255)),
            ("5000K", rgb(255, 228, 206)),
        ], [
            ("Amber", rgb(255, 191, 0)),
            ("Deep Sky Blue", rgb(0, 191, 255)),
            ("<VioletMagenta>", rgb(191, 0, 255)),
            ("6500K", rgb(255, 254, 250)),
        ],[
            ("Yellow", rgb(255, 255, 0)),
            ("Cyan", rgb(0, 255, 255)),
            ("Magenta", rgb(255, 0, 255)),
            ("15000K", rgb(181, 205, 255))
        ]
    ]
    return render_template("remote_template.html", color_map=color_map, message=message)



if __name__ == "__main__":
    manager.run()
