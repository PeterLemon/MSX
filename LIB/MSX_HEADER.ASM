//================
// MSX ROM Header
//================
dw $4241 // Identification Code ($4241 = ROM Cartridge, $4443 = SUBROM)
dw Start // Start Address ($0000..$BFFF)
fill 12  // Fill Rest Of 16 Byte Header With Zeros