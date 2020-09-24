//================
// MSX ROM Header
//================
db "AB"  // Identification Code ("AB" ($4241) = ROM Cartridge, "CD" ($4443) = SUBROM)
dw Start // Pointer To Start Of InitCode, 0 IF No InitCode ($0000..$BFFF)
dw $0000 // Pointer To CALL Statement Handler, 0 IF No Statement Handler ($0000..$BFFF)
dw $0000 // Pointer To Expansion Device Handler, 0 IF No Expansion Device Handler ($0000..$BFFF)
dw $0000 // Pointer To Start Of Tokenized BASIC-Program, 0 IF No Tokenized BASIC-Program ($0000..$BFFF)
fill 6   // Fill Rest Of 16 Byte Header With Zeros (Room Reserved For Future Extensions) 