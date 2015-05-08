#Converts the contents of 'letters.txt' into an array
#that can be used by the arduino program. The result
#of the conversion is in the file 'array.txt'.

f = open("letters.txt", "r")
lines = f.readlines()

out = "{\n"

for i in range(0, 26):
    startLine = i * 8
    slice = lines[startLine + 1  : startLine + 8]
    out += "{"
    mout = ""
    for s in slice:
        s = s.replace("\n","")
        n = int(s, 2)
        mout += str(n) + ","
    out += mout[0:len(mout) - 1] + "},\n"

out = out[0:len(out)-2] + "\n};"

print out
w = open("array.txt", "w")
w.write(out)
w.close()

f.close()
