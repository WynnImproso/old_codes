#import the following modules; they are similar to C's libraries

import os
import sys
import time
import serial
import pygame
import re

#import matplotlib.pyplot as plt


distance = []
#initialize the pygame module
pygame.init() 

#sets the size of the frame of the application
screen=pygame.display.set_mode((1000,550),0,32)

#sets variable name for RGB value of a color
textcolor= (23, 234, 255)
linecolor=(87, 107, 47)
pointcolor= (255,255,0)
graphcolor= (255,0,0)

#sets an empty array
points=[]
data=[1,2,3]
savedValue=""
        
#sets initial value for the variables
x=50
z=0
i=0
y=0
c=0
check='a'
scheck=0

#uses the system clock to manipulate the speed
clock=pygame.time.Clock()


speedx=10

#sets the font to default
font = pygame.font.Font(None, 20)
fontTitle = pygame.font.Font(None, 50)
fontName = pygame.font.Font(None, 30)
#initializes and opens the serial port
try:
    serialy = serial.Serial('COM3')
    scheck=1
except serial.SerialException as e:
    print e

    
#creates a continuous loop
while True:

    titleString= fontTitle.render ("Simple Harmonic Motion", 10,(255,0,0))
    screen.blit (titleString, (570, 470))

    titleName= fontName.render ("VISSER", 10,(255,0,0))
    screen.blit (titleName, (895, 510))    

    texts = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
    colnum = -8
    colnum2 = 415
    #guide numbers (y-axis)
    for i in range(0,17):
        texts[i] = font.render(str(colnum),5,textcolor)
        colnum += 1
        screen.blit(texts[i],(20,colnum2))
        colnum2 += 75

    atexts = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
    colnum3 = 1
    colnum4 = 120
    #guide numbers (x-axis)

    #guide lines (horizontal)
    colnum5 = 35
    for i in range(0,27):
        pygame.draw.line(screen,linecolor,(50,colnum5),(950,colnum5),1)
        colnum5 += 15

    #guide lines (vertical)
    colnum6 = 125
    for i in range(0,12):
        pygame.draw.line(screen,linecolor,(colnum6,20),(colnum6,445),1)
        colnum6 += 75


    #draws the axis        
    pygame.draw.line(screen, linecolor, (50, 20), (50, 467), 2)     #vertical
    pygame.draw.line(screen, linecolor, (20, 445), (1180,445), 2)   #horizontal

    #calls for event if any action is done during the execution of the program    
    for event in pygame.event.get():

        #executed if the close button is clicked
        if event.type == pygame.QUIT:
            #print distance
            serialy.close()
            pygame.quit()
            pygame.Destroy() #something haha

        #executed if the down key is pressed    
        if event.type== pygame.KEYDOWN : 
            #speedx=speedx-50
            i+=1
            w= str (i)
            pygame.image.save (screen, 'Screenshot'+ w+ '.jpg')
        if event.type== pygame.KEYUP : 
            speedx=speedx+50
       

    #generates the wave form
    milli=clock.tick()
    seconds=milli/400.
    dmx=seconds*speedx
    x+= dmx

    
#    filehandle0=open(os.path.join("" , "data.csv"),'w')
#    filehandle1=open(os.path.join("", "data.txt"),'w')
#    filehandle0.write(savedValue)
#    filehandle1.write(savedValue3)
#    filehandle0.close()
#    filehandle1.close()

    
    if x > 950:               
        x=55                  
        del points[:]         
        screen.fill([0,0,0])  
    if scheck==1:
        s=serialy.readline()
        #print s
        savedValue= savedValue + s

        #removes the possible white spaces
        valueRead= s.rstrip(" \r\n\n")
        valueRead= valueRead.rstrip("Distance:")
        

        data= re.split(',',valueRead)
        valueRead= data[0]
        del data[:]
        valueRead= valueRead.rstrip(" cm")
        
        print valueRead
        
        if valueRead != '':
            try:
                y0 = float(valueRead)
                y = 300-int(8*y0)
            except:
                dale=0
        if y>445:
                y=445
        if y<35:
                y=35
        pos= (int(x), y)
        distance.append(y)
        circle= pygame.draw.circle(screen, pointcolor, pos, 2 ,0)
        points.append (pos)

        #draws a graph if the points array is not empty
        if len(points) > 1:
            lines= pygame.draw.lines(screen, graphcolor, False, points, 1)

    
    time.sleep(0.0000000000001)
    pygame.display.update()
    
