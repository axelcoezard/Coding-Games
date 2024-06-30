import sys
import math

while True:
    higher = 0
    higher_index = 0
    for i in range(8):
        mountain_h = int(input())
        if mountain_h > higher: 
            higher = mountain_h
            higher_index = i
    print(higher_index)