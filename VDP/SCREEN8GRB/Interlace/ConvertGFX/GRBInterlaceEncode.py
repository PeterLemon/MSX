# MSX2 24-Bit RGB -> 8-Bit GRB332 Screen 8 Interlace Image Encoder
import struct
RGB = open("Moogle256x424.bin", "rb").read() # Big-Endian 24-Bit RGB888 Binary Image
GRBEven = [] # 8-Bit GRB332 Binary Image Even Lines (Maximum 256 Colors On Screen)
GRBOdd  = [] # 8-Bit GRB332 Binary Image Odd  Lines (Maximum 256 Colors On Screen)
width  = 256 # Image Width
height = 212 # Image Height
header = False # Select To Append .SC8 7 Byte Header (True/False)

# Header
if header == True: # IF (header == True) Append 7 Byte Header
    GRBEven.append(0xFE) # Byte 0: $FE
    GRBEven.append(0x00) # Byte 1: $00
    GRBEven.append(0x00) # Byte 2: $00
    GRBEven.append(width-1)  # Byte 3: Image  Width -1
    GRBEven.append(height-1) # Byte 4: Image Height -1
    GRBEven.append(0x00) # Byte 5: $00
    GRBEven.append(0x00) # Byte 6: $00

    GRBOdd.append(0xFE) # Byte 0: $FE
    GRBOdd.append(0x00) # Byte 1: $00
    GRBOdd.append(0x00) # Byte 2: $00
    GRBOdd.append(width-1)  # Byte 3: Image  Width -1
    GRBOdd.append(height-1) # Byte 4: Image Height -1
    GRBOdd.append(0x00) # Byte 5: $00
    GRBOdd.append(0x00) # Byte 6: $00

# RGB888 -> GRB332 Encode Even Lines
i = 0 # Byte Counter
while i < len(RGB): # For Length Of RGB Data
    # For RGB888 Dots (3 Bytes) Encode GRB332 Dots (1 Byte)
    R8 = struct.unpack('B', RGB[i:i+1]) # Dot RGB888 Values
    G8 = struct.unpack('B', RGB[i+1:i+2])
    B8 = struct.unpack('B', RGB[i+2:i+3])

    G3 = G8[0] >> 5 # G3 = G8 >> 5
    R3 = R8[0] >> 5 # R3 = R8 >> 5
    B2 = B8[0] >> 6 # B2 = B8 >> 6

    GRBEven.append((G3<<5) | (R3<<2) | B2) # Append Dot (1 Byte)

    i += 3 # Increment Byte Count To Encode Next GRB332 Dot

    if i % width == 0: i += width * 3 # IF i / width Remainder == 0, Skip Next Scanline

# RGB888 -> GRB332 Encode Odd Lines
i = width * 3 # Byte Counter
while i < len(RGB): # For Length Of RGB Data
    # For RGB888 Dots (3 Bytes) Encode GRB332 Dots (1 Byte)
    R8 = struct.unpack('B', RGB[i:i+1]) # Dot RGB888 Values
    G8 = struct.unpack('B', RGB[i+1:i+2])
    B8 = struct.unpack('B', RGB[i+2:i+3])

    G3 = G8[0] >> 5 # G3 = G8 >> 5
    R3 = R8[0] >> 5 # R3 = R8 >> 5
    B2 = B8[0] >> 6 # B2 = B8 >> 6

    GRBOdd.append((G3<<5) | (R3<<2) | B2) # Append Dot (1 Byte)

    i += 3 # Increment Byte Count To Encode Next GRB332 Dot

    if i % width == 0: i += width * 3 # IF i / width Remainder == 0, Skip Next Scanline

with open('MoogleEven256x212.sc8', 'wb') as f:
    for b in GRBEven: f.write(struct.pack('B', b))
with open('MoogleOdd256x212.sc8', 'wb') as f:
    for b in GRBOdd: f.write(struct.pack('B', b))
