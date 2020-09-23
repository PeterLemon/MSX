// MSX AY8910 PSG Axel-F Song Pattern demo by krom (Peter Lemon):
arch msx.cpu
output "PSGAxel-F.rom", create
fill $8000 // Set ROM Size (32KB)

macro ChannelPatternTone(CHANNEL, KEY, PERIODTABLE) { // Channel Pattern Tone Calculation
  ld l,(ix+({KEY}*2))   // L = Pattern List (LSB)
  ld h,(ix+({KEY}*2)+1) // H = Pattern List (MSB)
  add hl,bc // HL += Pattern Offset Index (BC)

  ld a,(hl)      // A = Period Table Offset
  cp SUST        // Compare A To SUST Character ($FE)
  jr z,{#}KEYEND // IF (A == SUST) Key End

  // Key OFF
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld e,a       // E = A
  set {KEY},e  // E = PSG Channel Tone Disable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)

  ld a,(hl)      // A = Period Table Offset
  cp REST        // Compare A To REST Character ($FF)
  jr z,{#}KEYEND // IF (A == REST) Key End

  // ELSE Channel: Key ON
  ld d,$00            // D = $00
  ld e,a              // E = Period Table Offset (A)
  ld hl,{PERIODTABLE} // HL = PeriodTable 16-Bit Address
  add hl,de           // HL += DE

  ld a,PSG_FINE_TUNE_{CHANNEL} // A = PSG Channel Fine Tune Address
  ld e,(hl)                    // E = PSG Channel Fine Tune
  inc hl                       // Increment Period Table Offset (HL++)
  call WRTPSG                  // PSG Write Data (A = PSG Address, E = PSG Data)

  ld a,PSG_COARSE_TUNE_{CHANNEL} // A = PSG Channel Course Tune Address
  ld e,(hl)                      // E = Channel Course Tune
  call WRTPSG                    // PSG Write Data (A = PSG Address, E = PSG Data)

  // Key ON
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld e,a       // E = A
  res {KEY},e  // E = PSG Channel Tone Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)
  {#}KEYEND: // Key End
}

macro ChannelPatternNoise(KEY) { // Channel Pattern Noise Calculation
  ld l,(ix+({KEY}*2))   // L = Pattern List (LSB)
  ld h,(ix+({KEY}*2)+1) // H = Pattern List (MSB)
  add hl,bc // HL += Pattern Offset Index (BC)

  ld a,(hl)      // A = Period Table Offset
  cp SUST        // Compare A To SUST Character ($FE)
  jr z,{#}KEYEND // IF (A == SUST) Key End

  // Key OFF
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld e,a       // E = A
  set {KEY},e  // E = PSG Channel Tone Disable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)

  ld a,(hl)      // A = Period Table Offset
  cp REST        // Compare A To REST Character ($FF)
  jr z,{#}KEYEND // IF (A == REST) Key End

  // ELSE Channel: Key ON
  ld a,PSG_NOISE_TUNE // A = PSG Noise Tune Address ($06)
  ld e,(hl)           // E = PSG Channel Noise Tune
  call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

  // Key ON
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld e,a       // E = A
  res {KEY},e  // E = PSG Channel Tone Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
  ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
  call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)
  {#}KEYEND: // Key End
}

// Constants
constant MaxQuant(128)   // Maximum Quantization ms
constant PatternSize(64) // Pattern Size (1..256)
constant ChannelCount(6) // Channel Count

origin $0000
base $4000 // Entry Point Of Code
include "LIB/MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB/MSX_SYSTEM.INC" // Include MSX System Routines
include "LIB/MSX_PSG.INC"    // Include MSX PSG Definitions

Start:

di   // Disable Interrupts
im 1 // Set Interrupt Mode 1
ei   // Enable Interrupts

// Disable All Channels
ld a,PSG_KEY   // A = PSG Channel Enable Address ($07)
ld e,%00111111 // E = PSG Channel Tone Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
call WRTPSG    // PSG Write Data (A = PSG Address, E = PSG Data)

// Setup Channel A,B,C Tones
ld a,PSG_MODE_VOL_A // A = PSG Channel A Mode/Volume Address ($08)
ld e,$10            // E = PSG Channel A Mode/Volume (Bit 4 Mode = 1, Bits 0..3 Volume = 0)
call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

ld a,PSG_MODE_VOL_B // A = PSG Channel B Mode/Volume Address ($09)
ld e,$10            // E = PSG Channel B Mode/Volume (Bit 4 Mode = 1, Bits 0..3 Volume = 0)
call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

ld a,PSG_MODE_VOL_C // A = PSG Channel C Mode/Volume Address ($0A)
ld e,$0F            // E = PSG Channel C Mode/Volume (Bit 4 Mode = 0, Bits 0..3 Volume = 15)
call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

StartSong:
  ld ix,PATTERNLIST // IX = Pattern List Address
  ld bc,$0000       // BC = 0 (Pattern Offset Index)

LoopSong:
  ld a,PSG_ENV_SHAPE // A = PSG Channel Volume Envelope Shape Address ($0D)
  ld e,$08           // E = PSG Channel Volume Envelope Shape (Bits 0..3 Shape = 8)
  call WRTPSG        // PSG Write Data (A = PSG Address, E = PSG Data)

  ld a,PSG_ENV_FINE_TUNE // A = PSG Channel Volume Envelope Period Fine Tune Address ($0B)
  ld e,$03               // A = PSG Channel Volume Envelope Period Fine Tune (Bits 0..7 Fine Tune = 3)
  call WRTPSG            // PSG Write Data (A = PSG Address, E = PSG Data)

  ld a,PSG_ENV_COARSE_TUNE // A = PSG Channel Channel Volume Envelope Period Coarse Tune Address ($0C)
  ld e,$40                 // E = Channel Channel Volume Envelope Period Coarse Tune (Bits 0..7 Coarse Tune = 64)
  call WRTPSG              // PSG Write Data (A = PSG Address, E = PSG Data)

  ChannelPatternTone(A, 0, PeriodTable) // Channel A Tone Pattern Calculation: Channel, Key, Period Table
  ChannelPatternTone(B, 1, PeriodTable) // Channel B Tone Pattern Calculation: Channel, Key, Period Table
  ChannelPatternTone(C, 2, PeriodTable) // Channel C Tone Pattern Calculation: Channel, Key, Period Table

  ChannelPatternNoise(3) // Channel A Noise Pattern Calculation: Key
  ChannelPatternNoise(4) // Channel A Noise Pattern Calculation: Key
  ChannelPatternNoise(5) // Channel A Noise Pattern Calculation: Key

  // Delay (VSYNCS)
  ld d,MaxQuant/15 // D = Count
  Wait:
    halt // Power Down CPU Until An Interrupt Occurs
    dec d
    jr nz,Wait // Decrement Count (D--), IF (Count != 0) Wait

  inc c                 // Increment Pattern Index Offset (LSB)
  ld a,c                // A = C (Pattern Index Offset)
  cp PatternSize        // Compare A To Pattern Size
  jr z,PatternIncrement // IF (A == Pattern Size) Pattern Increment
  jr PatternEnd         // ELSE Pattern End

  PatternIncrement: // Channel A..C Pattern Increment
    ld de,ChannelCount*2 // DE = Channel Count * 2
    add ix,de            // IX += DE (Pattern List Offset += Channel Count * 2)

    // Compare Pattern List End Address
    ld a,PATTERNLISTEND    // A = Pattern List End Offset (LSB)
    cp ixl                 // Compare A To Pattern List Offset (LSB)
    jr nz,PatternIncEnd    // IF (Pattern List Offset != Pattern List End Offset) Pattern Increment End, ELSE Set Pattern Loop Offset
    ld a,PATTERNLISTEND>>8 // A = Pattern List End Offset (MSB)
    cp ixh                 // Compare A To Pattern List Offset (MSB)
    jr nz,PatternIncEnd    // IF (Pattern List Offset != Pattern List End Offset) Pattern Increment End, ELSE Set Pattern Loop Offset

    // Set Pattern Loop Offset
    ld ix,PATTERNLISTLOOP // IX = Pattern List Loop

  PatternIncEnd:
    ld bc,$0000 // BC = 0 (Pattern Offset Index)

  PatternEnd:
    jp LoopSong // Loop Song

PeriodTable: // Period Table Used For PSG Tone Freqencies
  PeriodTable() // Timing, 9 Octaves: A0..G9# (108 Words)

PATTERN00: // Pattern 00: Rest (Channel A..C)
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 1
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 2
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 3
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 4

PATTERN01: // Pattern 01: Saw Tooth (Channel A Tone)
  db F4,   SUST, SUST, REST, G4s,  SUST, REST, F4,   SUST, F4,   A4s,  SUST, F4,   SUST, D4s,  SUST // 1
  db F4,   SUST, SUST, REST, C5,   SUST, REST, F4,   SUST, F4,   C5s,  SUST, C5,   SUST, G4s,  SUST // 2
  db F4,   SUST, C5,   SUST, F5,   SUST, F4,   D4s,  SUST, D4s,  C4,   SUST, G4,   SUST, F4,   SUST // 3
  db SUST, SUST, SUST, SUST, SUST, SUST, SUST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 4

PATTERN02: // Pattern 02: Bass (Channel B Tone)
  db F2,   SUST, SUST, SUST, F3,   SUST, SUST, D2s,  SUST, D3s,  C2,   SUST, C3,   SUST, D2s,  SUST // 9
  db F2,   SUST, SUST, SUST, F3,   SUST, SUST, SUST, SUST, C2,   C3,   SUST, D3s,  SUST, F3,   SUST // 10
  db C2s,  SUST, SUST, SUST, C3s,  SUST, SUST, D2s,  SUST, D3s,  C2,   SUST, C3,   SUST, D2s,  SUST // 11
  db F2,   SUST, SUST, SUST, SUST, SUST, SUST, SUST, SUST, F3,   C3,   SUST, A2s,  SUST, G2s,  SUST // 12
PATTERN03: // Pattern 03: Bass (Channel B Tone)
  db F2,   SUST, SUST, SUST, F3,   SUST, SUST, D2s,  SUST, D3s,  C2,   SUST, C3,   SUST, D2s,  SUST // 21
  db F2,   SUST, SUST, SUST, F3,   SUST, SUST, SUST, SUST, C2,   C3,   SUST, D3s,  SUST, F3,   SUST // 22
  db C2s,  SUST, SUST, SUST, C3s,  SUST, SUST, D2s,  SUST, SUST, SUST, SUST, D3s,  SUST, SUST, SUST // 23
  db F2,   SUST, SUST, SUST, F3,   SUST, SUST, SUST, SUST, F3,   C3,   SUST, A2s,  SUST, G2s,  SUST // 24

PATTERN04: // Pattern 04: Staccato Saw Tooth (Channel A Tone)
  db REST, REST, F4,   SUST, SUST, SUST, F4,   G4,   SUST, G4,   SUST, G4,   F4,   SUST, F4,   SUST // 21
  db SUST, REST, F4,   SUST, F4,   SUST, F4,   G4,   SUST, G4,   F4,   SUST, F4,   SUST, SUST, SUST // 22
  db SUST, REST, C4s,  SUST, C4s,  SUST, C4s,  SUST, C4s,  D4s,  SUST, D4s,  SUST, D4s,  SUST, D4s  // 23
  db D4s,  SUST, F4,   SUST, F4,   SUST, F4,   SUST, D4s,  F4,   SUST, F4,   SUST, SUST, SUST, REST // 24

PATTERN05: // Pattern 05: Staccato Saw Tooth (Channel C Tone)
  db REST, REST, C5,   SUST, SUST, SUST, C5,   D5s,  SUST, D5s,  SUST, D5s,  D5,   SUST, D5,   SUST // 21
  db SUST, REST, C5,   SUST, C5,   SUST, C5,   D5s,  SUST, D5s,  D5,   SUST, C5,   SUST, SUST, SUST // 22
  db SUST, REST, G4s,  SUST, G4s,  SUST, G4s,  SUST, G4s,  A4s,  SUST, A4s,  SUST, A4s,  SUST, A4s  // 23
  db A4s,  SUST, C5,   SUST, C5,   SUST, C5,   SUST, A4s,  C5,   SUST, C5,   SUST, SUST, SUST, REST // 24

PATTERN06: // Pattern 06: Kick Drum (Channel A Noise)
  db 15,   REST, REST, REST, REST, REST, REST, 15,   REST, 15,   15,   REST, REST, REST, REST, REST // 13
  db 15,   REST, REST, REST, 15,   REST, REST, REST, REST, 15,   15,   REST, REST, REST, REST, REST // 14
  db 15,   REST, REST, REST, 15,   REST, REST, 15,   REST, 15,   15,   REST, 15,   REST, 15,   REST // 15
  db 15,   REST, REST, REST, 15,   REST, REST, REST, REST, 15,   15,   REST, 15,   REST, 15,   REST // 16

PATTERN07: // Pattern 07: Snare (Channel B Noise)
  db REST, REST, REST, REST, 1,    REST, REST, REST, REST, REST, REST, REST, 1,    REST, REST, REST // 17
  db REST, REST, REST, REST, 1,    REST, REST, REST, REST, REST, REST, REST, 1,    REST, REST, REST // 18
  db REST, REST, REST, REST, 1,    REST, REST, REST, REST, REST, REST, REST, 1,    REST, REST, REST // 19
  db REST, REST, REST, REST, 1,    REST, REST, REST, REST, REST, REST, REST, 1,    REST, REST, REST // 20

PATTERN08: // Pattern 08: Clap (Channel C Noise)
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 9
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 10
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 11
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, 3,    3,    REST, 3,    REST, 3,    REST // 12
PATTERN09: // Pattern 09: Clap (Channel C Noise)
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 13
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, 3,    REST, 3,    REST, 3,    REST // 14
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST, REST // 15
  db REST, REST, REST, REST, REST, REST, REST, REST, REST, 3,    3,    REST, 3,    REST, 3,    REST // 16

PATTERNLIST:
  dw PATTERN01,PATTERN00,PATTERN00,PATTERN00,PATTERN00,PATTERN00 // Channel A..C Tone, Channel A..C Noise Pattern Address List
  dw PATTERN01,PATTERN00,PATTERN01,PATTERN00,PATTERN00,PATTERN00 // Channel A..C Tone, Channel A..C Noise Pattern Address List
  dw PATTERN00,PATTERN02,PATTERN00,PATTERN00,PATTERN00,PATTERN08 // Channel A..C Tone, Channel A..C Noise Pattern Address List
  dw PATTERN00,PATTERN02,PATTERN00,PATTERN06,PATTERN00,PATTERN09 // Channel A..C Tone, Channel A..C Noise Pattern Address List
PATTERNLISTLOOP:
  dw PATTERN01,PATTERN02,PATTERN01,PATTERN06,PATTERN07,PATTERN08 // Channel A..C Tone, Channel A..C Noise Pattern Address List
  dw PATTERN01,PATTERN02,PATTERN01,PATTERN06,PATTERN07,PATTERN08 // Channel A..C Tone, Channel A..C Noise Pattern Address List

  dw PATTERN04,PATTERN03,PATTERN05,PATTERN06,PATTERN07,PATTERN08 // Channel A..C Tone, Channel A..C Noise Pattern Address List
  dw PATTERN04,PATTERN03,PATTERN05,PATTERN06,PATTERN07,PATTERN08 // Channel A..C Tone, Channel A..C Noise Pattern Address List
PATTERNLISTEND: