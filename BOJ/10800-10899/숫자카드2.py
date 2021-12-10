import sys
input = sys.stdin.readline

n = int(input())
A = list(map(int,input().split()))
m = int(input())
B = list(map(int,input().split()))

A.sort()

def bs(num, bound):
    start, end = 0, n
    while(start < end):
        mid = (start + end) // 2
        if bound == 0:
            if A[mid] < num:
                start = mid + 1
            else:
                end = mid
        else:
            if A[mid] <= num:
                start = mid + 1
            else:
                end = mid
    return end

result = []
for i in B:
    result.append(bs(i,1) - bs(i,0))
print(*result)