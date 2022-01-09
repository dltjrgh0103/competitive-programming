import sys
input = sys.stdin.readline

T = int(input())
INF = float('inf')

for _ in range(T) :
    
    N = int(input())
    arr = list(map(int, input().split()))
    result = 0
    
    while len(arr) >= 2 :
        find_idx = len(arr) - 2
        
        for i in range(len(arr) - 2) :
            if arr[i] <= arr[i + 2] :
                find_idx = i
                break
            
        a1 = arr.pop(find_idx)
        a2 = arr.pop(find_idx)
        B = a1 + a2
            
        arr.insert(find_idx, B)
        result += B
        B_index = find_idx
           
        while B_index > 0 and arr[B_index - 1] < arr[B_index]:
            arr[B_index], arr[B_index - 1] = arr[B_index - 1], arr[B_index]
            B_index -= 1

print(result)