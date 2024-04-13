import serial
import time

ser = serial.Serial('COM3', 2400)

data_received = ""

def print_speed(bytes_transferred, elapsed_time):
    speed = (bytes_transferred * 8) / elapsed_time
    print("Transmission Speed: {:.2f} bits/second".format(speed))

start_time = time.time()

while True:
    if ser.in_waiting > 0:
        data_received += ser.read().decode('utf-8')
        bytes_transferred = len(data_received)
        elapsed_time = time.time() - start_time
        print_speed(bytes_transferred, elapsed_time)
        print(data_received, end="")
        data_received = ""

ser.close()
