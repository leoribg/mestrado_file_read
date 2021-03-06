import os
import time
#from teste_leo import *



#for i in range (9022, 9280, 2):
#    main(i * 100000, "{0}.txt".format(i))
#    if (i < 9075 or i > 9150) :
#        s = "python power_final.py --center-freq=" + str(i * 100000) + " --filename=" + str(i) + ".txt"
#        print(s)


s = "./program"
for i in range (9022, 9280, 2):
    if (i < 9074 or i > 9150) :
        s += " " + str(i) + ".txt"
        #print(i)
print(s)


s = "./program"
for i in range (9022, 9280, 2):
    if (i < 9074 or i > 9150) :
        s += " " + str(i) + ".txt"
        #print(i)
print(s)