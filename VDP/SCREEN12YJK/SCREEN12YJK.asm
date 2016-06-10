// MSX2+ Screen 12 YJK Demo by krom (Peter Lemon):
arch msx.cpu
output "SCREEN12YJK.rom", create
fill $8000 // Set ROM Size (32KB)

macro YJKTile(source, dest, width, height) { // YJK Color Tile Block Transfer From Memory To VRAM
  ld hl,{source} // HL = Memory Source Address
  ld de,{dest}   // DE = VRAM Destination Address
  ld a,{height}  //  A = Number Of Tile Lines
  -
    push af // Store Number Of Tile Lines
    push de // Store VRAM Destination Address
    push hl // Store Memory Source Address
    ld bc,{width} // BC = Data Length
    call LDIRVM   // CALL System Routine To Block Transfer From Memory To VRAM

    pop hl        // HL = Memory Source Address
    ld de,{width} // DE = $0080
    add hl,de     // HL += $0080
    pop de // DE = VRAM Destination Address
    inc d  // DE += $0100 (VRAM Destination Address To Next Scanline Down)

    pop af  // A = Number Of Tile Lines
    dec a   // A-- (Decrement Number Of Tile Lines)
    jr nz,- // IF (Number Of Tile Lines != Zero) Copy Tile
}

origin $0000
base $4000 // Entry Point Of Code
include "LIB\MSX.INC"        // Include MSX Definitions
include "LIB\MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB\MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  // Set Screen Mode 8
  ld a,8 // A = Screen Mode 8
  call CHGMOD // CALL System Routine To Change Screen Mode

  // Set Bit 3 In VDP Register 25 To Turn YJK Mode On (Screen 12)
  ld c,25 // C = VDP Register Number
  ld b,%00001000 // B = Data To Write
  call WRTVDP // CALL System Routine To Write Data To VDP Register

  // Block Transfer YJK Color Tiles From Memory To VRAM
  YJKTile(BGYJK, $0000, 128, 106) // Top Left Tile
  YJKTile(BGYJK, $0080, 128, 106) // Top Right Tile
  YJKTile(BGYJK, $6A00, 128, 106) // Bottom Left Tile
  YJKTile(BGYJK, $6A80, 128, 106) // Bottom Right Tile

Loop:
  jr Loop

insert BGYJK, "Image128x106.s12" // Include BG YJK 128x106 Color Data (13568 Bytes)