from pwn import *
from algo_new import *
import random

board = [['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_'],
         ['_', '_', '_', '_', '_', '_', '_', '_', '_']]

flag_board = board.copy()

def isMatch(message, match):
	if (match in message):
		return True
	else:
		return False

def cleanline(line):

	line2 = line.decode('utf-8')
	line_req = line2.strip()

	return line_req

counter1 = 0

def add_line_to_board(line):
	global counter1

	for j in line:
		if (j!=' '):
			board[int(counter1/9)][int(counter1%9)] = j
			counter1+=1


def editBoard():
	global counter1
	counter1 = 0
	game = 'Game'
		# for checking if its a newgame or not
	line = sh.readline()
	line_to_use = cleanline(line)
	print(line_to_use)
		
	if (isMatch(line_to_use, game)):
		for i in range(10):
			line = sh.readline()
			line_to_use = cleanline(line)
			print(line_to_use)
			if (i >= 0 and i < 9 ):
				add_line_to_board(line_to_use)
		return
		
		# if it's not a newgame and just a continuing match
	else:
		for i in range(10):
			if (i >= 0 and i < 9):
				add_line_to_board(line_to_use)
			if (i!=8):
				line = sh.readline()
				line_to_use = cleanline(line)
				print(line_to_use)
		return



def printBoard():
    for i in range(9):
        print(board[i])

#printBoard()

# Driver
