// MSX2 Screen 8 GRB Interlace Demo by krom (Peter Lemon):
arch msx.cpu
output "SCREEN8GRBInterlace.rom", create
fill $20000 // Set ROM Size (128KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB\MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB\MSX_SYSTEM.INC" // Include MSX System Routines

//---------------------------------------------------------------------------------------
//   Funtion: Set VRAM (17-Bit Address: $00000..$1FFFF) In VDP & Enable It To Be Written
//            This Is Used To Write Auto-Increment Data To VRAM
//     Input: BHL = VRAM Address
//    Output:   C = CPU Port #$98 (VDP Port #0)
// Registers: AF
// Available: MSX2
//---------------------------------------------------------------------------------------
SETWRITE:
  ld a,($0007) // Main-ROM Must Be Selected On Page $0000..$3FFF
  inc a        // A++
  ld c,a       // C = CPU Port #$99 (VDP Port #1)
 
  // Write VRAM Address Bits A14..A16 To VDP Register 14 (MSX2 & Later)
  ld a,h  // A = H (VRAM Address HI Byte)
  and $C0 // A &= $C0 (Mask VRAM Address Bits A14..A15)
  or b    // A |= B (VRAM Address Bit A16)
  rlca    // A Rotate Left
  rlca    // A Rotate Left (A = VRAM Address Bits A14..A16)

  di          // Disable Interrupts
  out (c),a   // Write VRAM Address Bits A14..A16 To VDP Port #1
  ld a,$80+14 // A = VDP Register 14 Address
  out (c),a   // Write VDP Register 14 Address To VDP Port #1

  // Write VRAM Address Bits A0..A13 & VRAM Data Write Flag To VDP Port #1
  ld a,h    // A = H (VRAM Address HI Byte)
  and $3F   // A &= $3F (Mask VRAM Address Bits A8..A13)
  or $40    // A |= $40 (Bit 6 = VRAM Data Write Flag)
  out (c),l // Write VRAM Address Bits A0..A7 To VDP Port #1
  out (c),a // Write VRAM Address Bits A8..A13 & VRAM Data Write Flag To VDP Port #1

  ei    // Enable Interrupts
  dec c // C = CPU Port #$98 (VDP Port #0)
  ret

//------------------------------------------------------------------------------------------
//   Funtion: Block Transfer From Memory To VRAM (Needs VRAM Address & Write Enable Set)
//     Input: HL = Memory Source Address, DE = Data Length, C = CPU Port #$98 (VDP Port #0)
//    Output: NONE
// Registers: AF
// Available: MSX
//------------------------------------------------------------------------------------------
NLDIRVM:
  ld a,(hl)     // A = Next Data Byte In Block To Copy
  inc hl        // Increment Memory Source Address (HL++)
  out (c),a     // Write Data Byte To CPU Port #$98 (VDP Port #0)
  dec de        // Decrement Data Length (DE--)
  ld a,0        // A = 0
  cp e          // Compare Data Length LO Byte (E) To Zero (A)
  jr nz,NLDIRVM // IF (Data Length LO Byte != 0) Copy Block
  cp d          // Compare Data Length HI Byte (D) To Zero (A)
  jr nz,NLDIRVM // IF (Data Length HI Byte != 0) Copy Block
  ret

Start:
  // Set Screen Mode 8
  ld a,8      // A = Screen Mode 8
  call CHGMOD // CALL System Routine To Change Screen Mode

  // Set Bit 7,3,2 In VDP Register 9: Bit 7 = 212 Lines, Bit 3 = Interlaced Mode, Bit 2 = Alternate Even/Odd Page (Screen 8)
  ld c,9         // C = VDP Register Number
  ld b,%10001100 // B = Data To Write
  call WRTVDP    // CALL System Routine To Write Data To VDP Register

  // Copy BG GRB Even Color Data Part A To VRAM
  ld hl,BGGRBEvenA // HL = Memory Source Address
  ld de,$0000      // DE = VRAM Destination Address
  ld bc,$1400      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part B To VRAM
  ld a,1           // A = Bank 1
  ld ($6000),a     // Store Bank 1
  ld hl,BGGRBEvenB // HL = Memory Source Address
  ld de,$1400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part C To VRAM
  ld a,2           // A = Bank 2
  ld ($6000),a     // Store Bank 2
  ld hl,BGGRBEvenC // HL = Memory Source Address
  ld de,$3400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part D To VRAM
  ld a,3           // A = Bank 3
  ld ($6000),a     // Store Bank 3
  ld hl,BGGRBEvenD // HL = Memory Source Address
  ld de,$5400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part E To VRAM
  ld a,4           // A = Bank 4
  ld ($6000),a     // Store Bank 4
  ld hl,BGGRBEvenE // HL = Memory Source Address
  ld de,$7400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part F To VRAM
  ld a,5           // A = Bank 5
  ld ($6000),a     // Store Bank 5
  ld hl,BGGRBEvenF // HL = Memory Source Address
  ld de,$9400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Even Color Data Part G To VRAM
  ld a,6           // A = Bank 6
  ld ($6000),a     // Store Bank 6
  ld hl,BGGRBEvenG // HL = Memory Source Address
  ld de,$B400      // DE = VRAM Destination Address
  ld bc,$2000      // BC = Data Length
  call LDIRVM      // CALL System Routine To Block Transfer From Memory To VRAM


  // Copy BG GRB Odd Color Data Part A To VRAM
  ld a,7          // A = Bank 7
  ld ($6000),a    // Store Bank 7
  ld b,$01        // BHL = VRAM Destination Address
  ld hl,$0000
  call SETWRITE   // CALL Routine To Set VRAM (17-Bit Address: $00000..$1FFFF) In VDP & Enable It To Be Written
  ld hl,BGGRBOddA // HL = Memory Source Address 
  ld de,$1400     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part B To VRAM
  ld a,8          // A = Bank 8
  ld ($6000),a    // Store Bank 8
  ld hl,BGGRBOddB // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part C To VRAM
  ld a,9          // A = Bank 9
  ld ($6000),a    // Store Bank 9
  ld hl,BGGRBOddC // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part D To VRAM
  ld a,10         // A = Bank 10
  ld ($6000),a    // Store Bank 10
  ld hl,BGGRBOddD // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part E To VRAM
  ld a,11         // A = Bank 11
  ld ($6000),a    // Store Bank 11
  ld hl,BGGRBOddE // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part F To VRAM
  ld a,12         // A = Bank 12
  ld ($6000),a    // Store Bank 12
  ld hl,BGGRBOddF // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Copy BG GRB Odd Color Data Part G To VRAM
  ld a,13         // A = Bank 13
  ld ($6000),a    // Store Bank 13
  ld hl,BGGRBOddG // HL = Memory Source Address
  ld de,$2000     // DE = Data Length
  call NLDIRVM    // CALL Routine To Block Transfer From Memory To VRAM

  // Set Bit 0,1,2,3,4,5 In VDP Register 2: Bit 5 = Display Page 1 (Screen 8)
  ld c,2         // C = VDP Register Number
  ld b,%00111111 // B = Data To Write
  call WRTVDP    // CALL System Routine To Write Data To VDP Register

Loop:
  jr Loop

insert BGGRBEvenA, "MoogleEven256x212.sc8", $0000, $1400 // Include BG GRB Even Color Data Part A (5120 Bytes)

// BANK 1
origin $02000
base $6000
insert BGGRBEvenB, "MoogleEven256x212.sc8", $1400, $2000 // Include BG GRB Even Color Data Part B (8192 Bytes)

// BANK 2
origin $04000
base $6000
insert BGGRBEvenC, "MoogleEven256x212.sc8", $3400, $2000 // Include BG GRB Even Color Data Part C (8192 Bytes)

// BANK 3
origin $06000
base $6000
insert BGGRBEvenD, "MoogleEven256x212.sc8", $5400, $2000 // Include BG GRB Even Color Data Part D (8192 Bytes)

// BANK 4
origin $08000
base $6000
insert BGGRBEvenE, "MoogleEven256x212.sc8", $7400, $2000 // Include BG GRB Even Color Data Part E (8192 Bytes)

// BANK 5
origin $0A000
base $6000
insert BGGRBEvenF, "MoogleEven256x212.sc8", $9400, $2000 // Include BG GRB Even Color Data Part F (8192 Bytes)

// BANK 6
origin $0C000
base $6000
insert BGGRBEvenG, "MoogleEven256x212.sc8", $B400, $2000 // Include BG GRB Even Color Data Part G (8192 Bytes)


// BANK 7
origin $0E000
base $6000
insert BGGRBOddA, "MoogleOdd256x212.sc8", $0000, $1400 // Include BG GRB Odd Color Data Part A (5120 Bytes)

// BANK 8
origin $10000
base $6000
insert BGGRBOddB, "MoogleOdd256x212.sc8", $1400, $2000 // Include BG GRB Odd Color Data Part B (8192 Bytes)

// BANK 9
origin $12000
base $6000
insert BGGRBOddC, "MoogleOdd256x212.sc8", $3400, $2000 // Include BG GRB Odd Color Data Part C (8192 Bytes)

// BANK 10
origin $14000
base $6000
insert BGGRBOddD, "MoogleOdd256x212.sc8", $5400, $2000 // Include BG GRB Odd Color Data Part D (8192 Bytes)

// BANK 11
origin $16000
base $6000
insert BGGRBOddE, "MoogleOdd256x212.sc8", $7400, $2000 // Include BG GRB Odd Color Data Part E (8192 Bytes)

// BANK 12
origin $18000
base $6000
insert BGGRBOddF, "MoogleOdd256x212.sc8", $9400, $2000 // Include BG GRB Odd Color Data Part F (8192 Bytes)

// BANK 13
origin $1A000
base $6000
insert BGGRBOddG, "MoogleOdd256x212.sc8", $B400, $2000 // Include BG GRB Odd Color Data Part G (8192 Bytes)