def decode(p):

    # Decode the first 7 characters, the row number
    row = 0
    i = 64
    for c in p[:6]:
        if c == "B":
            row += i
        
        i /= 2


    # Decode last 3 characters, column number
    col = 0
    i = 4
    for c in p[7:]:
        if c == "R":
            col += i

        i /= 2

    # Return a tuple with the format (row, seat, id)
    return (row, col, (row * 8) + col)





if __name__ == "__main__":
    input = open("day5.input", "r")
    text = input.read()
    input.close()

    # Split string into array of lines
    passes = text.splitlines()

    i = 0
    ids = []
    for p in passes:
        d = decode(p)
        ids.append(int(d[2]))
        i += 1

    print(f"Read {i} boarding passes")
    print(f"Max seat id {max(ids)}")
