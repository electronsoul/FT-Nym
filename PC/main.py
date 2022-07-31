import serial
import time

para = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for" \
       " predicting that the next banking crisis would be triggered by MSME lending, saying" \
       " postmortem is easier than taking action when it was required. Rajan, who had as the" \
       " chief economist at IMF warned of impending financial crisis of 2008, in a note to a" \
       " parliamentary committee warned against ambitious credit targets and loan waivers, saying" \
       " that they could be the sources of next banking crisis. Government should focus on sources" \
       " of the next crisis, not just the last one. In particular, government should refrain from" \
       " setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved" \
       " by abandoning appropriate due diligence, creating the environment for future NPAs," \
       " ``Rajan said in the note.`` Both MUDRA loans as well as the Kisan Credit Card, while popular," \
       " have to be examined more closely for potential credit risk. Rajan, who was RBI governor" \
       " for three years till September 2016, is currently."

START_BYTE = '~'
STOP_BYTE = '!'


def getCRC(mesg):
    CRCREG = 0x0
    CRCDIVISOR = 0x39
    temp = mesg
    n = mesg
    count = 0
    count = int(mesg).bit_length()
    i = 0
    while i < count:
        temp &= 0x1
        if temp ^ (CRCREG & 0x1):
            CRCREG >>= 1
            CRCREG ^= CRCDIVISOR
        else:
            CRCREG >>= 1
        temp = mesg
        temp >>= 1
        mesg >>= 1
        i = i + 1
    return CRCREG


sp = serial.Serial(baudrate=2400,
                   port='/dev/ttyUSB0',
                   timeout=1)

i = 0

'''
for _itr_ in range(0, len(para[:10])):
    sp.write(START_BYTE.encode('utf-8'))

    pktdata = para.__getitem__(i)
    previous = time.time()
    sp.write(repr((i % 10) + 1).encode('utf-8'))  # pktid
    sp.write(pktdata.encode('utf-8'))  # get data
    temp = time.time()

    rcx = int.from_bytes(sp.read(), "big")  # get crc
    rate = 1 / (temp - previous)
    previous = temp

    if i == 10:
        pktdata = '0'  # It is done so to simulate a error if occurs.

    sentDataCRC = getCRC(ord(pktdata))
    recievedDataCRC = getCRC(rcx)

    print("\n")
    print("RxCRC: ", recievedDataCRC, "ComputedCRC: ", sentDataCRC)

    if sentDataCRC == recievedDataCRC:
        sp.write(b'^')
        if sp.read() == b'>':
            print("Sending: ", pktdata, "PacketID:", i + 1)
            print("Current rate: ", rate, " Bytes/Sec")
            print("Successfully Transmitted and Saved In EEPROM")
    else:
        print("CRC Check Failed... Error In Transmission")
        print("Erroneous Packed ID: ", i + 1)
    i = i + 1
    time.sleep(1)
'''

for _itr_ in range(0, len(para[:9])):
    previous = time.time()
    if sp.read() == b'~':
        pktdata = sp.read()
        temp = time.time()
        if sp.read() == b'>':
            rxDataCRC = getCRC(ord(pktdata))
            expectedcrc = getCRC(ord(para.__getitem__(_itr_)))
            print("Received:",para.__getitem__(_itr_)) ##
            if rxDataCRC == expectedcrc:
                print("CRC result Success") ##
            else:
                print("CRC result Fail") ##
            rate = 1 / (temp - previous)
            previous = temp
            print("Reception Speed: ", rate, "Bytes/Sec")
    time.sleep(1)
