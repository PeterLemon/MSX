// MSX2+ Screen 8 GRB Image Demo by krom (Peter Lemon):
arch msx.cpu
output "SCREEN8GRBImage.rom", create
fill $10000 // Set ROM Size (64KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB\MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB\MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  // Set Screen Mode 8
  ld a,8      // A = Screen Mode 8
  call CHGMOD // CALL System Routine To Change Screen Mode

  // Copy BG GRB Color Data Part A To VRAM
  ld hl,BGGRBA // HL = Memory Source Address
  ld de,$0000  // DE = VRAM Destination Address
  ld bc,$1400  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part B To VRAM
  ld a,1       // A = Bank 1
  ld ($6000),a // Store Bank 1
  ld hl,BGGRBB // HL = Memory Source Address
  ld de,$1400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part C To VRAM
  ld a,2       // A = Bank 2
  ld ($6000),a // Store Bank 2
  ld hl,BGGRBC // HL = Memory Source Address
  ld de,$3400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part D To VRAM
  ld a,3       // A = Bank 3
  ld ($6000),a // Store Bank 3
  ld hl,BGGRBD // HL = Memory Source Address
  ld de,$5400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part E To VRAM
  ld a,4       // A = Bank 4
  ld ($6000),a // Store Bank 4
  ld hl,BGGRBD // HL = Memory Source Address
  ld de,$7400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part F To VRAM
  ld a,5       // A = Bank 5
  ld ($6000),a // Store Bank 5
  ld hl,BGGRBD // HL = Memory Source Address
  ld de,$9400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Color Data Part G To VRAM
  ld a,6       // A = Bank 6
  ld ($6000),a // Store Bank 6
  ld hl,BGGRBD // HL = Memory Source Address
  ld de,$B400  // DE = VRAM Destination Address
  ld bc,$2000  // BC = Data Length
  call LDIRVM  // CALL System Routine To Block Transfer From Memory To VRAM

Loop:
  jr Loop

insert BGGRBA, "Moogle256x212.sc8", $0000, $1400 // Include BG GRB Color Data Part A (5120 Bytes)

// BANK 1
origin $02000
base $6000
insert BGGRBB, "Moogle256x212.sc8", $1400, $2000 // Include BG GRB Color Data Part B (8192 Bytes)

// BANK 2
origin $04000
base $6000
insert BGGRBC, "Moogle256x212.sc8", $3400, $2000 // Include BG GRB Color Data Part C (8192 Bytes)

// BANK 3
origin $06000
base $6000
insert BGGRBD, "Moogle256x212.sc8", $5400, $2000 // Include BG GRB Color Data Part D (8192 Bytes)

// BANK 4
origin $08000
base $6000
insert BGGRBE, "Moogle256x212.sc8", $7400, $2000 // Include BG GRB Color Data Part E (8192 Bytes)

// BANK 5
origin $0A000
base $6000
insert BGGRBF, "Moogle256x212.sc8", $9400, $2000 // Include BG GRB Color Data Part F (8192 Bytes)

// BANK 6
origin $0C000
base $6000
insert BGGRBG, "Moogle256x212.sc8", $B400, $2000 // Include BG GRB Color Data Part G (8192 Bytes)