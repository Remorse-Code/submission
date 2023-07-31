from pwn import *

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

def flag_marker(i, j):
    global flag_board
    flag_board[i][j] = 'F'

def co_ord_check(check):
    for i in check:
        if i < 0 and i > 8:
            #print('co-ord out of range')
            return False

'''making cases'''

'''case 1 is to make the sq. group for the inner foldings'''
'''
case - 1
A B
C D
'''
# case - 1

'''check for blank'''
def check_blank(board, i, j):
    if (board[i][j] == '_' and i>=0 and j>=0 and i<=len(board) and j<=len(board)):
        return True
    else:
        return False

def check_nearby_rule_1(board, i, j):
    counter = 0
    x_axis = 0
    y_axis = 0
    for x in range(i-1, i+1, 1):
        for y in range(j-1, j+1, 1):
            if x != i and y != j:
                check = [x, y]
                var = co_ord_check(check)
                if var != False:
                    if board[x][y] == '_':
                        x_axis = x
                        y_axis = y
                        counter += 1
    if counter == 1:
        return [x_axis, y_axis]
    else:
        return False

'''check for the rule 1'''
def rule_1(board, i, j):
    # for D
    if (check_blank(board, i+1, j+1)):
        return check_nearby_rule_1(board, i, j)
    else:
        # for A
        if (check_blank(board, i-1, j-1)):
            return check_nearby_rule_1(board, i, j)
        else:
            # for C
            if (check_blank(board, i+1, j-1)):
                return check_nearby_rule_1(board, i, j)
            else:
                # for B
                if (check_blank(board, i-1, j+1)):
                    return check_nearby_rule_1(board, i, j)
                else:
                    return False

def rule_1_app(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] != '_':
                co_ord = rule_1(board, i, j)
                if co_ord != False:
                    flag_marker(i, j)
                else:
                    return False

'''
case - 2 
here we go on to get the outer folding 5 part group
A B C
D E F
G H I

logic - gonna work with E to find out how to get it done
satis - satisfied by the squares near it
'''

def counter_satis(board, i, j):
    counter = 0
    for x in range(i+1, j+1, 1):
        for y in range(i+1, j+1, 1):
            if x != i and y != j:
                if board[x][y] == '_':
                    counter+=1
    return 

def rule_2_satis_check(board, i, j):
    counter = 0
    for x in range(i+1, j+1, 1):
        for y in range(i+1, j+1, 1):
            if x != i and y != j:
                check = [x, y]
                var = co_ord_check(check)
                if var != False:
                    if board[x][y] == '_':
                        counter+=1
    if counter == board[i][j]:
        for x in range(i+1, j+1, 1):
            for y in range(i+1, j+1, 1):
                if x != i and y != j:
                    check = [x, y]
                    var = co_ord_check(check)
                    if var != False:
                        if board[x][y] == '_':
                            flag_marker(x, y)


'''
case 3
opening by checking the satisfactory conditions, i.e flags already marked
'''

def check_satis(board, flag_board, i, j):
    counter=0
    for x in range(i-1, i+1, 1):
        for y in range(j-1, j+1, 1):
            check = [x, y]
            var = co_ord_check(check)
            if var != False:
                if flag_board[x][y] == 'F':
                    counter+=1
    if counter == board[i][j]:
        for x in range(i-1, i+1, 1):
            for y in range(j-1, j+1, 1):
                check = [x, y]
                var = co_ord_check(check)
                if var != False:
                    if flag_board[x][y] == '_':
                        if board[x][y] == '_':
                            open = [x, y]
                            return open

'''
check for if all flags have been marked
'''

def check_flag_board():
    counter = 0
    global flag_board
    for i in range(9):
        for j in range(9):
            if flag_board[i][j]:
                counter+=1
    if counter == 10:
        print('all flags have been marked')
        open_all()

def open_all():
    global flag_board
    global board
    for i in range(9):
        for j in range(9):
            if flag_board[i][j] != 'F':
                if board[i][j] == '_':
                    move = i+','+j # type: ignore
                    move = str(move).encode('ascii')
                    sh.sendline(move)