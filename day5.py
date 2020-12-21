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


    print(decode("BFFFBBFRRR"))
    print(decode("FFFBBBFRRR"))
    print(decode("BBFFBBFRLL"))

    # List of all possible seats to check against
    all_seats = []
    for x in range(0, 128):
        for y in range(0, 8):
            all_seats.append((x * 8) + y)
    
    for n in all_seats:
        if (n not in ids) and (n - 1 in ids) and (n + 1 in ids):
            print("Found seat!!")
            print(n)
