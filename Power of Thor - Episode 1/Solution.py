import sys
import math

light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]

HEIGHT = 18
WIDTH = 40

thorX = initial_tx
thorY = initial_ty

while True:
    remaining_turns = int(input())  

    directionX = ""
    directionY = ""
    if thorX > light_x: 
        thorX -= 1
        directionX = "W"
    elif thorX < light_x:
        thorX += 1   
        directionX = "E"

    if thorY > light_y: 
        thorY -= 1
        directionY = "N"
    elif thorY < light_y: 
        thorY += 1
        directionY = "S" 

    print(directionY + directionX)
