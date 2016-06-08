//================
// MSX ROM Header
//================
db "AB"  // Identification Code ("AB" ($4241) = ROM Cartridge, "CD" ($4443) = SUBROM)
dw Start // Start Address ($0000..$BFFF)
fill 12  // Fill Rest Of 16 Byte Header With Zeros