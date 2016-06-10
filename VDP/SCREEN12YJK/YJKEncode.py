# MSX2+ / Turbo-R 24-Bit RGB -> 8-Bit YJK Screen 12 Image Encoder
#
# Each YJK Block Uses 4 Dots At A Time:
# Dot | C7 C6 C5 C4 C3 | C2 C1 C0 | <- 8-Bits
#  1  |       Y1       |    KL    |
#  2  |       Y2       |    KH    |
#  3  |       Y3       |    JL    |
#  4  |       Y4       |    JH    |
#
# RGB -> YJK Calculation:
#     B   R   G | J = R - Y
# Y = - + - + - |
#     2   4   8 | K = G - Y
import struct
RGB = open("Image.bin", "rb").read() # Big-Endian 24-Bit RGB888 Binary Image
YJK = [] # 8-Bit YJK Binary Image (Maximum 19,268 Colors On Screen)
width  = 256 # Image Width (Needs To Be A Multiple Of 4)
height = 212 # Image Height
header = True # Select To Append .S12/.SCC 7 Byte Header (True/False)

# Header
if header == True: # IF (header == True) Append 7 Byte Header
    YJK.append(0xFE) # Byte 0: $FE
    YJK.append(0x00) # Byte 1: $00
    YJK.append(0x00) # Byte 2: $00
    YJK.append(width-1)  # Byte 3: Image  Width -1
    YJK.append(height-1) # Byte 4: Image Height -1
    YJK.append(0x00) # Byte 5: $00
    YJK.append(0x00) # Byte 6: $00

# RGB -> YJK Encode
i = 0 # Byte Counter
while i < len(RGB): # For Length Of RGB Data
    # For 4 * RGB Dots (12 Bytes) Encode 4 * YJK Dots (4 Bytes)
    R1 = struct.unpack('B', RGB[i:i+1]) # 1st Dot RGB Values
    G1 = struct.unpack('B', RGB[i+1:i+2])
    B1 = struct.unpack('B', RGB[i+2:i+3])

    R2 = struct.unpack('B', RGB[i+3:i+4]) # 2nd Dot RGB Values
    G2 = struct.unpack('B', RGB[i+4:i+5])
    B2 = struct.unpack('B', RGB[i+5:i+6])
    
    R3 = struct.unpack('B', RGB[i+6:i+7]) # 3rd Dot RGB Values
    G3 = struct.unpack('B', RGB[i+7:i+8])
    B3 = struct.unpack('B', RGB[i+8:i+9])

    R4 = struct.unpack('B', RGB[i+9:i+10]) # 4th Dot RGB Values
    G4 = struct.unpack('B', RGB[i+10:i+11])
    B4 = struct.unpack('B', RGB[i+11:i+12])

    Y1 = (B1[0]>>1) + (R1[0]>>2) + (G1[0]>>3) # Y1 = (B1/2) + (R1/4) + (G1/8)
    Y2 = (B2[0]>>1) + (R2[0]>>2) + (G2[0]>>3) # Y2 = (B2/2) + (R2/4) + (G2/8)
    Y3 = (B3[0]>>1) + (R3[0]>>2) + (G3[0]>>3) # Y3 = (B3/2) + (R3/4) + (G3/8)
    Y4 = (B4[0]>>1) + (R4[0]>>2) + (G4[0]>>3) # Y4 = (B4/2) + (R4/4) + (G4/8)

    R = (R1[0] + R2[0] + R3[0] + R4[0]) >> 2 # R = (R1 + R2 + R3 + R4) / 4
    G = (G1[0] + G2[0] + G3[0] + G4[0]) >> 2 # G = (G1 + G2 + G3 + G4) / 4
    Y = (Y1 + Y2 + Y3 + Y4) >> 2 # Y = (Y1 + Y2 + Y3 + Y4) / 4

    J = R - Y # J = R - Y
    K = G - Y # K = G - Y
    J >>= 3 # Convert J To Signed 6-Bits
    K >>= 3 # Convert K To Signed 6-Bits

    Y1 &= 0b11111000 # Convert Y1 To 5-Bits
    Y2 &= 0b11111000 # Convert Y2 To 5-Bits
    Y3 &= 0b11111000 # Convert Y3 To 5-Bits
    Y4 &= 0b11111000 # Convert Y4 To 5-Bits

    JL = J & 0b000111 # JL = J & %000111 (3-Bits)
    JH = J & 0b111000 # JH = J & %111000
    JH >>= 3 # Convert JH To 3-Bits

    KL = K & 0b000111 # KL = K & %000111 (3-Bits)
    KH = K & 0b111000 # KH = K & %111000
    KH >>= 3 # Convert KH To 3-Bits

    YJK.append(Y1+KL) # Append 1st Dot Of YJK Block (1 Byte)
    YJK.append(Y2+KH) # Append 2nd Dot Of YJK Block (1 Byte)
    YJK.append(Y3+JL) # Append 3rd Dot Of YJK Block (1 Byte)
    YJK.append(Y4+JH) # Append 4th Dot Of YJK Block (1 Byte)

    i += 12 # Increment Byte Count To Encode Next YJK 4 Dot Block

with open('Image.s12', 'wb') as f:
    for b in YJK: f.write(struct.pack('B', b))
