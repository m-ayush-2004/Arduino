import math
import time
import matplotlib.pyplot as p
import numpy as np
import pandas as pd
import itertools as it
from matplotlib.animation import FuncAnimation
import serial
import time

# make sure the 'COM#' is set according the Windows Device Manager
ser = serial.Serial('COM7', 9800, timeout=1)

data = []

index= it.count()
r_vals=[]
g_vals=[]
b_vals=[]
nums=[]
x_vals=[]
def animate(i):
    # time.sleep(1)
    try:
        line = ser.readline()   # read a byte string
        if line:
            string=line.decode()
            string = list(string.split("]"))  # convert the byte string to a unicode string
            string = list(string[0][1:].split(","))
            nums = list(map(int,string)) # convert the unicode string to an int
            print(nums)
            data.append(nums) # add int to data list
    except:
        nums=[0,0,0]
    print(nums)
    x_vals.append(next(index))
    r_vals.append(nums[0]/(sum(nums)))
    g_vals.append(nums[1]/(sum(nums)))
    b_vals.append(nums[2]/(sum(nums)))
    p.cla()
    p.plot(x_vals,r_vals, color="red")
    p.plot(x_vals,g_vals, color="green")
    p.plot(x_vals,b_vals, color="blue")
    p.tight_layout()
    p.grid(True)
time.sleep(2)
ani = FuncAnimation(p.gcf(),animate,interval=0.1)
p.show()