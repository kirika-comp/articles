p = int(input())

fac = []
pp = 2
v = p - 1
while v >= pp * pp:
    e = 0
    while v % pp == 0:
        e += 1
        v //= pp
    if e > 0:
        fac.append(pp)
    pp += 1
if v > 1:
    fac.append(v)

g = 2
while g < p:
    if pow(g, p - 1, p) != 1:
        print(str(p) + ' is not a prime')
        exit()
    ok = True
    for pp in fac:
        if pow(g, (p - 1) // pp, p) == 1:
            ok = False
            break
    if ok:
        print('The smallest generator is ' + str(g))
        exit()
    g += 1
