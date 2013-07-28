DELTA = ord('a') - ord('A')
DASH = '-'

file = open("exer-2-2011-6-dash.py")
text = file.read()

dash = False

for c in text:
    if 'a' <= c <= 'z':
        code = ord(c) - DELTA
        print(chr(code), end='')
        dash = False
    elif ('A' <= c <= 'Z') or ('0' <= c <= '9'):
        print(c, end='')
        dash = False
    elif not dash:
        print(DASH, end='')
        dash = True
