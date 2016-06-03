//================
// MSX ROM Header
//================
db "AB"  // Required ASCII Text
dw Start // Reset Vector
fill 12  // Fill Rest Of 16 Byte Header With Zeros