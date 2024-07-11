class Chess:
    def __init__(self, players_name):
        self.board = [['R','K','B','Z','U','B','K','R'], 
                      ['P','P','P','P','P','P','P','P'], 
                      ['_','_','_','_','_','_','_','_'], 
                      ['_','_','_','_','_','_','_','_'],
                      ['_','_','_','_','_','_','_','_'],
                      ['_','_','_','_','_','_','_','_'],
                      ['p','p','p','p','p','p','p','p'], 
                      ['r','k','b','z','u','b','k','r']]
        
        self.round = 1
        self.players = players_name
        self.turn = None
        self.points = [0, 0]
        self.count = [8, 2, 2, 2, 1, 8, 2, 2, 2, 1]
    
    
    
    def control(self):
        while not self.is_checkmate():
            self.turn = self.players[(self.round % 2) - 1]
            
            captured_piece = self.is_anything_captured()
            self.counting_points(captured_piece.lower())

            self.display_board(self.turn)

            piece, coordinate = self.select_piece()
            piece_lower = piece.lower()

            new_coordinate = self.select_move(piece_lower, coordinate)
            
            self.upgrade_board(piece, coordinate, new_coordinate) 
            self.round += 1



    def select_piece(self): 
        while True and self.turn == self.players[0]:
            piece, coordinate = input('\nEnter Piece and Coordinate (p-a7): ').lower().split('-')

            col, row = list('abcdefgh').index(coordinate[0]), int(coordinate[-1]) - 1

            if self.board[row][col] != piece:
                print('Invalid Piece:')

            else: 
                return piece, [row, col]
            
            
        while True and self.turn == self.players[1]:
            piece, coordinate = input('\nEnter Piece and Coordinate (P-a2): ').upper().split('-')

            col, row = list('ABCDEFGH').index(coordinate[0]), int(coordinate[-1]) - 1

            if self.board[row][col] != piece:
                print('Invalid Piece:')

            else:
                return piece, [row, col]


    # Move Selecting Functions  
    def can_go(self, piece, coordinate, move):
        min_row = min(coordinate[0], move[0])
        max_row = max(coordinate[0], move[0])
        min_col = min(coordinate[-1], move[-1])
        max_col = max(coordinate[-1], move[-1])

        match piece:
            case 'p':
                return True
            


            case 'b':
                if (max_row == move[0]) and (max_col == move[-1]): 
                    for iter, row in enumerate(range(min_row + 1, max_row)):
                        if not self.is_place_available([row, (min_col + iter + 1)], wanted_move=move):
                            return False
                        
                elif (max_row == coordinate[0]) and (max_col == coordinate[-1]): 
                    for iter, row in enumerate(range(max_row - 1, min_row, -1)):
                        if not self.is_place_available([row, max_col - iter - 1], wanted_move=move):
                            return False

                elif (max_row == move[0]) and (max_col == coordinate[-1]): 
                    for iter, col in enumerate(range(max_col - 1, min_col, -1)):
                        if not self.is_place_available([min_row + iter + 1, col], wanted_move=move):
                            return False
                        
                else: 
                    for iter, col in enumerate(range(min_col + 1, max_col)):
                        if not self.is_place_available([max_row - iter - 1, col], wanted_move=move):
                            return False

                return True
            
    

            case 'k':
                return True
            


            case 'r':
                if (coordinate[0] == move[0]):
                    for col in range((min_col + 1), max_col):
                        if not self.is_place_available([move[0], col], wanted_move=move):
                            return False
                        
                else:
                    for row in range((min_row + 1), max_row):
                        if not self.is_place_available([row, move[-1]], wanted_move=move):
                            return False   
                return True
            


            case 'z':
                if (coordinate[0] == move[0]):
                    for col in range((min_col + 1), max_col):
                        if not self.is_place_available([move[0], col], wanted_move=move):
                            return False


                elif (coordinate[-1] == move[-1]):
                    for row in range((min_row + 1), max_row):
                        if not self.is_place_available([row, move[-1]], wanted_move=move):
                            return False 


                else:  
                    if (max_row == move[0]) and (max_col == move[-1]): 
                        for iter, row in enumerate(range(min_row + 1, max_row)):
                            if not self.is_place_available([row, (min_col + iter + 1)], wanted_move=move):
                                return False
                        
                    elif (max_row == coordinate[0]) and (max_col == coordinate[-1]): 
                        for iter, row in enumerate(range(max_row - 1, min_row, -1)):
                            if not self.is_place_available([row, max_col - iter - 1], wanted_move=move):
                                return False

                    elif (max_row == move[0]) and (max_col == coordinate[-1]): 
                        for iter, col in enumerate(range(max_col - 1, min_col, -1)):
                            if not self.is_place_available([min_row + iter + 1, col], wanted_move=move):
                                return False
                        
                    else: 
                        for iter, col in enumerate(range(min_col + 1, max_col)):
                            if not self.is_place_available([min_row - iter - 1, col], wanted_move=move):
                                return False
                return True



            case 'u':
                return True



    def is_place_available(self, move, wanted_move=[]):
        if self.turn == self.players[0]:
            if self.board[move[0]][move[-1]] in 'pbkrzu':
                return False
            elif self.board[move[0]][move[-1]] == "_":
                return True 
            elif (self.board[move[0]][move[-1]] in "PBKRZU") and (move == wanted_move):
                return True
            return False
        
        elif self.turn == self.players[-1]:
            if self.board[move[0]][move[-1]] in 'PBKRZU':
                return False
            elif self.board[move[0]][move[-1]] == "_":
                return True 
            elif self.board[move[0]][move[-1]] in "pbkrzu" and (move == wanted_move):
                return True
            return False



    def is_move_available(self, piece, coordinate, move):
        match piece:
            case 'p':
                if self.turn == self.players[0]:
                    if (move[0] - coordinate[0] == -1) and (move[-1] == coordinate[-1]) or \
                        ((move[0] - coordinate[0] == -2) and (move[-1] == coordinate[-1]) and (coordinate[0] == 6)):
                        return True
                    
                    elif (self.board[coordinate[0] - 1][coordinate[-1] + 1] in 'PBKRZU') and ((move[0] - coordinate[0] == -1) and (move[-1] - coordinate[-1] == 1)):
                        return True
                    
                    elif (self.board[coordinate[0] - 1][coordinate[-1] - 1] in 'PBKRZU') and ((move[0] - coordinate[0] == -1) and (move[-1] - coordinate[-1] == -1)):
                        return True
                    
                else:
                    if (move[0] - coordinate[0] == 1) and (move[-1] == coordinate[-1]) or \
                        ((move[0] - coordinate[0] == 2) and move[-1] == coordinate[-1] and coordinate[0] == 1):
                        return True
                    
                    elif (self.board[coordinate[0] + 1][coordinate[-1] + 1] in 'pbkrzu') and ((move[0] - coordinate[0] == 1) and (move[-1] - coordinate[-1] == 1)):
                        return True
                    
                    elif (self.board[coordinate[0] + 1][coordinate[-1] - 1] in 'pbkrzu') and ((move[0] - coordinate[0] == 1) and (move[-1] - coordinate[-1] == -1)):
                        return True
                    
                return False

            case 'b':
                if abs(move[0] - coordinate[0]) == abs(move[-1] - coordinate[-1]):
                    return True
                else: return False
        
            case 'k':
                if (abs(move[0] - coordinate[0]) == 2 and abs(move[-1] - coordinate[-1]) == 1) or (abs(move[0] - coordinate[0]) == 1 and abs(move[-1] - coordinate[-1]) == 2):
                    return True
                else: return False

            case 'r':
                if ((move[0] != coordinate[0]) and (move[1] == coordinate[1])) or ((move[1] != coordinate[1]) and (move[0] == coordinate[0])):
                    return True
                else: return False

            case 'z':
                if ((move[0] != coordinate[0]) and (move[1] == coordinate[1])) or ((move[1] != coordinate[1]) and (move[0] == coordinate[0])) or (abs(move[0] - coordinate[0]) == abs(move[-1] - coordinate[-1])):
                    return True
                else: return False

            case 'u':
                if ((abs(move[0] - coordinate[0]) == 1) and (move[-1] == coordinate[-1])) or ((abs(move[-1] - coordinate[-1]) == 1) and \
                (move[0] == coordinate[0])) or ((abs(move[0] - coordinate[0]) == 1) and (abs(move[-1] - coordinate[-1]))):
                    return True
                else: return False



    def select_move(self, piece, coordinate):
        move = input('\nEnter a move (a8): ')
        col, row = list('abcdefgh').index(move[0]), int(move[-1]) - 1

        while (not self.is_move_available(piece, coordinate, [row, col])) or (not self.is_place_available([row, col], wanted_move=[row, col])) or (not self.can_go(piece, coordinate, [row, col])):
            if not self.is_move_available(piece, coordinate, [row, col]):
                print('\nInvalid Move!')
            
            elif not self.is_place_available([row, col]):
                print('Place is occupied!')

            elif not self.can_go(piece, coordinate, [row, col]):
                print('There is obstacle!')

            move = input('\nEnter a move (a8): ') 
            col, row = list('abcdefgh').index(move[0]), int(move[-1]) - 1 
                

        return [row, col]




    # Controlling Game
    def is_checkmate(self):
        return False



    def counting_points(self, captured_piece):
        points = {'p': 1, 'b': 3, 'k': 3, 'r': 5, 'z': 9}
        self.points[(self.round % 2) - 2] += points.get(captured_piece, 0)

    
    def is_anything_captured(self):
        prev_count = self.count.copy()
        for index, piece in enumerate('pbkrzPBKRZ'):
            count = 0
            for col in range(len(self.board)):                
                count += self.board[col].count(piece)
                self.count[index] = count

            if prev_count[index] != self.count[index]:
                return piece
        
        return 'a'


    # Board Functions 
    def upgrade_board(self, piece, prev_coordinate, coordinate):
        self.board[prev_coordinate[0]][prev_coordinate[-1]] = '_'
        self.board[coordinate[0]][coordinate[-1]] = piece


    
    def display_board(self, player):
        print('\n')
        print('\t', end='')

        for i in (list('abcdefgh')):
            print(i, end='\t')
        print('\n', 70*'_')

        for index, row in enumerate(range(len(self.board))):
            print('\n')
            print((index + 1), '|', end='\t')
            for col in range(len(self.board[0])):
                if self.board[row][col] == ' ':
                    print('_', end='\t')
                else:
                    print(self.board[row][col], end='\t')

        print(player + '\'s Turn!')

        print('\n')
        print('Points:')
        print(15*'_')
        print(self.players[0] + ':', self.points[0])
        print(self.players[1] + ':', self.points[-1])