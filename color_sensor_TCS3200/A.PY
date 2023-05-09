import matplotlib.pyplot as p
from numpy import square
x=[0.98,1.96,2.94,3.92,4.9]
y=square([0.1425,0.1625,0.1925,0.2005,0.2335])
p.plot(x,y,marker='o')
for a,b in zip(x, y): 
    p.text(a,b,"({:.2f},{:.2f})".format(a,b))
print(sum(y)/sum(x))
p.grid()
p.show()