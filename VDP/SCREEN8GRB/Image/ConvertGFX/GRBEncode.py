# MSX2 / MSX2+ / Turbo-R 24-Bit RGB -> 8-Bit GRB332 Screen 8 Image Encoder
import struct
RGB = open("Moogle256x212.bin", "rb").read() # Big-Endian 24-Bit RGB888 Binary Image
GRB = [] # 8-Bit GRB332 Binary Image (Maximum 256 Colors On Screen)
width  = 256 # Image Width (Needs To Be A Multiple Of 4)
height = 212 # Image Height
header = False # Select To Append .SC8 7 Byte Header (True/False)

# Header
if header == True: # IF (header == True) Append 7 Byte Header
    GRB.append(0xFE) # Byte 0: $FE
    GRB.append(0x00) # Byte 1: $00
    GRB.append(0x00) # Byte 2: $00
    GRB.append(width-1)  # Byte 3: Image  Width -1
    GRB.append(height-1) # Byte 4: Image Height -1
    GRB.append(0x00) # Byte 5: $00
    GRB.append(0x00) # Byte 6: $00

# RGB888 -> GRB332 Encode
i = 0 # Byte Counter
while i < len(RGB): # For Length Of RGB Data
    # For RGB888 Dots (3 Bytes) Encode GRB332 Dots (1 Byte)
    R8 = struct.unpack('B', RGB[i:i+1]) # Dot RGB888 Values
    G8 = struct.unpack('B', RGB[i+1:i+2])
    B8 = struct.unpack('B', RGB[i+2:i+3])

    G3 = G8[0] >> 5 # G3 = G8 >> 5
    R3 = R8[0] >> 5 # R3 = R8 >> 5
    B2 = B8[0] >> 6 # B2 = B8 >> 6

    GRB.append((G3<<5) | (R3<<2) | B2) # Append Dot (1 Byte)

    i += 3 # Increment Byte Count To Encode Next RGB332 Dot

with open('Moogle256x212.sc8', 'wb') as f:
    for b in GRB: f.write(struct.pack('B', b))
