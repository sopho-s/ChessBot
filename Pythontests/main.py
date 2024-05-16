import chess
import copy
board = chess.Board()
legal_moves = list(board.legal_moves)
boards = [board]
tempboards = []
for i in range(4):
    string = ""
    count = 0
    for t in range(len(boards)):
        legal_moves = list(boards[t].legal_moves)
        for move in legal_moves:
            tempboard = copy.deepcopy(boards[t])
            currmove = chess.Move.from_uci(str(move))
            tempboard.push(currmove)
            tempboards.append(tempboard)
            string += tempboard.fen().split(" ")[0] + "\n"
            count += 1
            if (count % 10000 == 0):
                print(f"{count} moves generated")
    file = open(f"ply{i}.txt", "w")
    file.write(string)
    file.close()
    print(len(tempboards))
    boards = []
    boards = copy.deepcopy(tempboards)
    tempboards = []