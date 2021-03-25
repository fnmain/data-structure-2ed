N, M = map(int, input().split())

for _ in range(N):
    line = input()
    stack = []
    yes = True
    for ch in line:
        if ch == 'S':
            if len(stack) < M:
                stack.append('S')
            else:
                yes = False
                break
        elif ch == 'X':
            if stack:
                stack.pop()
            else:
                yes = False
                break
    if yes and len(stack) == 0:
        print('YES')
    else:
        print('NO')