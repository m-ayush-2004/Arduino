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
ser = serial.Serial('COM12', 9800, timeout=1)

data = [[0,0,0],[1,1,1]]

index= it.count()
r_vals=[]
g_vals=[]
b_vals=[]
nums=[]
x_vals=[]
def animate(i):
    nums=data[-1]
    try:
        line = ser.readline()   # read a byte string
        if x_vals[-1]%200==0:
            for i in range(10):
                line =ser.readline()
                print(i,line)
                # try:
                # except:
                #     print("broken")
                #     break
        if line:
            string=line.decode()
            string = list(string.split(","))
            nums = list(map(int,string)) # convert the unicode string to an int
            data.append(nums) # add int to data list
    except:
        nums=data[-1]
    x_vals.append(next(index))
    r_vals.append(nums[0])
    g_vals.append(nums[1])
    b_vals.append(nums[2])
    p.cla()
    p.plot(x_vals,r_vals, color="red")
    p.plot(x_vals,g_vals, color="green")
    p.plot(x_vals,b_vals, color="blue")
    p.tight_layout()
    p.grid(True)

ani = FuncAnimation(p.gcf(),animate,interval=0.1,frames=1000)
p.show()