// MSX2+ Screen 12 YJK Image Demo by krom (Peter Lemon):
arch msx.cpu
output "SCREEN12YJKImage.rom", create
fill $10000 // Set ROM Size (64KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB\MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB\MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  // Set Screen Mode 8
  ld a,8      // A = Screen Mode 8
  call CHGMOD // CALL System Routine To Change Screen Mode

  // Set Bit 3 In VDP Register 25 To Turn YJK Mode On (Screen 12)
  ld c,25        // C = VDP Register Number
  ld b,%00001000 // B = Data To Write
  call WRTVDP    // CALL System Routine To Write Data To VDP Register

  // Copy BG YJK Color Data Part A To VRAM
  ld hl,BGYJKA // HL = Memory Source Address
  ld de,$0000  // DE = VRAM Destination Address
  ld bc,$1400  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part B To VRAM
  ld a,1       // A = Bank 1
  ld ($6000),a // Store Bank 1
  ld hl,BGYJKB // HL = Memory Source Address
  ld de,$1400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part C To VRAM
  ld a,2       // A = Bank 2
  ld ($6000),a // Store Bank 2
  ld hl,BGYJKC // HL = Memory Source Address
  ld de,$3400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part D To VRAM
  ld a,3       // A = Bank 3
  ld ($6000),a // Store Bank 3
  ld hl,BGYJKD // HL = Memory Source Address
  ld de,$5400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part E To VRAM
  ld a,4       // A = Bank 4
  ld ($6000),a // Store Bank 4
  ld hl,BGYJKE // HL = Memory Source Address
  ld de,$7400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part F To VRAM
  ld a,5       // A = Bank 5
  ld ($6000),a // Store Bank 5
  ld hl,BGYJKF // HL = Memory Source Address
  ld de,$9400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG YJK Color Data Part G To VRAM
  ld a,6       // A = Bank 6
  ld ($6000),a // Store Bank 6
  ld hl,BGYJKG // HL = Memory Source Address
  ld de,$B400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

Loop:
  jr Loop

insert BGYJKA, "Lenna256x212.s12", $0000, $1400 // Include BG YJK Color Data Part A (5120 Bytes)

// BANK 1
origin $02000
base $6000
insert BGYJKB, "Lenna256x212.s12", $1400, $2000 // Include BG YJK Color Data Part B (8192 Bytes)

// BANK 2
origin $04000
base $6000
insert BGYJKC, "Lenna256x212.s12", $3400, $2000 // Include BG YJK Color Data Part C (8192 Bytes)

// BANK 3
origin $06000
base $6000
insert BGYJKD, "Lenna256x212.s12", $5400, $2000 // Include BG YJK Color Data Part D (8192 Bytes)

// BANK 4
origin $08000
base $6000
insert BGYJKE, "Lenna256x212.s12", $7400, $2000 // Include BG YJK Color Data Part E (8192 Bytes)

// BANK 5
origin $0A000
base $6000
insert BGYJKF, "Lenna256x212.s12", $9400, $2000 // Include BG YJK Color Data Part F (8192 Bytes)

// BANK 6
origin $0C000
base $6000
insert BGYJKG, "Lenna256x212.s12", $B400, $2000 // Include BG YJK Color Data Part G (8192 Bytes)