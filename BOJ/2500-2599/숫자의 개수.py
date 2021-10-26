import sys

l = []
for _ in range(3):
    l.append(int(sys.stdin.readline()))

num = list(str(l[0]*l[1]*l[2]))

for i in range(10):
    cnt = 0
    for j in num:
        if i == int(j):
            cnt += 1
    print(cnt)
