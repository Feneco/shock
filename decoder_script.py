# this code is used to optimize the rainbow code tables used in esp32_shockcollar.ino
# by reverse engineering the sent signals

def call_s(l):
    s = ""
    b = True
    for i in l:
        if i < 500:
            s += ("1" if b else "0")*1
        elif i >= 500 and i< 1000:
            s += ("1" if b else "0")*3
        elif i >= 1000:
            s += ("1" if b else "0")*6
        b = not b
    return s[::-1]
    
startSequenzPt1 = [1472, 730, 725, 231, 233, 720, 233, 720, 233, 719, 233, 720]
startSequenzPt2 = [725, 231, 723, 230, 249, 720, 722, 231, 233, 720, 233, 720, 723, 231, 233, 719, 237, 719, 723, 231, 722, 231, 722, 231, 233, 731, 233, 719, 723, 230, 723, 231, 236, 720]
endSequenz = [723, 230, 723, 231, 722, 231, 722, 231, 233, 720, 232]
shock1 = [233, 719, 234, 719, 723, 231]
shock2 = [237, 719, 723, 231, 722, 231]
vibrate1 = [233, 719, 722, 231, 233, 719]
vibrate2 = [725, 231, 233, 719, 722, 231]
sound1 = [723, 230, 233, 720, 233, 719]
sound2 = [725, 231, 722, 231, 233, 719]

print(len(startSequenzPt1))
print(len(startSequenzPt2))
print(len(endSequenz))
print(len(shock1))
print(len(shock2))
print(len(vibrate1))
print(len(vibrate2))
print(len(sound1))
print(len(sound2))

print(call_s(startSequenzPt1))
print(call_s(startSequenzPt2))
print(call_s(endSequenz))
print(call_s(shock1))
print(call_s(shock2))
print(call_s(vibrate1))
print(call_s(vibrate2))
print(call_s(sound1))
print(call_s(sound2))

print(hex(int(call_s(startSequenzPt1), 2)))
print(hex(int(call_s(startSequenzPt2), 2)))
print(hex(int(call_s(endSequenz), 2)))
print(hex(int(call_s(shock1), 2)))
print(hex(int(call_s(shock2), 2)))
print(hex(int(call_s(vibrate1), 2)))
print(hex(int(call_s(vibrate2), 2)))
print(hex(int(call_s(sound1), 2)))
print(hex(int(call_s(sound2), 2)))

# 0x2, 0x22, 0x2e, 0x3f
# 0x1, 0x77, 0x11, 0x77, 0x71, 0x17, 0x11, 0x71, 0x77
# 0x11, 0x77, 0x77
# 0x7, 0x11
# 0x7, 0x71
# 0x1, 0x71
# 0x7, 0x17
# 0x1, 0x17
# 0x1, 0x77