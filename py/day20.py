m, n = 0,0
rooms = [bytearray([0 for _ in range(1<<9)]) for _ in range(1<<9)]
def parse(f,x,y,d):
    global m,n
    while 1:
        c = f.next()
        if c == 'N': y+=1
        elif c == 'E': x+=1
        elif c == 'S': y-=1
        elif c == 'W': x-=1
        elif c == '(':
            while parse(f, x, y, d): pass
            continue
        elif c == '|': return 1
        else:  return 0
        d+=1
        if not rooms[x][y]:
            rooms[x][y] = 1
            if d > m: m = d
            if d > 999: n+=1
with open("input") as f: parse((lambda: [(yield c) for c in f.read()[1:-1]])(), 1<<8, 1<<8, 0)
print "%d\n%d" % (m, n)
