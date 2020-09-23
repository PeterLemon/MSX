// MSX AY8910 PSG Twinkle Song demo by krom (Peter Lemon):
arch msx.cpu
output "PSGTwinkle.rom", create
fill $8000 // Set ROM Size (32KB)

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

// Setup Channel A Tone
ld a,PSG_MODE_VOL_A // A = PSG Channel A Mode/Volume Address ($08)
ld e,$0F            // E = PSG Channel A Mode/Volume (Bit 4 Mode = 0, Bits 0..3 Volume = 15)
call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

LoopSong:
  ld bc,SONGCHANA // BC = SONGCHANA 16-Bit Address

  PSGCHANA: // PSG Channel A
    ld a,(bc)        // A = Channel A: Period Table Offset
    cp SUST          // Compare A To SUST Character ($FE)
    jr z,PSGCHANAEnd // IF (A == SUST) Channel A: PSGCHANA End

    // Key OFF
    ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
    call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
    ld e,a       // E = A
    set 0,e      // E = PSG Channel A Tone Disable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
    ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
    call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)

    ld a,(bc)        // A = Channel A: Period Table Offset
    cp REST          // Compare A To REST Character ($FF)
    jr z,PSGCHANAEnd // IF (A == REST) Channel A: PSGCHANA End

    // ELSE Channel A: Key ON
    ld d,$00          // D = $00
    ld e,a            // E = Period Table Offset (A)
    ld hl,PeriodTable // HL = PeriodTable 16-Bit Address
    add hl,de         // HL += DE

    ld a,PSG_FINE_TUNE_A // A = PSG Channel A Fine Tune Address ($00)
    ld e,(hl)            // E = PSG Channel A Fine Tune
    inc hl               // Increment Period Table Offset (HL++)
    call WRTPSG          // PSG Write Data (A = PSG Address, E = PSG Data)

    ld a,PSG_COARSE_TUNE_A // A = PSG Channel A Course Tune Address ($01)
    ld e,(hl)              // E = Channel A Course Tune
    call WRTPSG            // PSG Write Data (A = PSG Address, E = PSG Data)

    // Key ON
    ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
    call RDPSG   // A = PSG Channel Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
    ld e,a       // E = A
    res 0,e      // E = PSG Channel A Tone Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
    ld a,PSG_KEY // A = PSG Channel Enable Address ($07)
    call WRTPSG  // PSG Write Data (A = PSG Address, E = PSG Data)
  PSGCHANAEnd:

  // 250 MS Delay (15 VSYNCS)
  ld d,15 // D = Count
  Wait:
    halt // Power Down CPU Until An Interrupt Occurs
    dec d
    jr nz,Wait // Decrement Count (D--), IF (Count != 0) Wait

  inc bc // BC++ (Increment Song Offset)

  ld a,SongEnd>>8 // IF (Song Offset != Song End) PSG Channel A
  cp b
  jp nz,PSGCHANA
  ld a,SongEnd
  cp c
  jp nz,PSGCHANA

  jp LoopSong // Loop Song

PeriodTable: // Period Table Used For PSG Tone Freqencies
  PeriodTable() // Timing, 9 Octaves: A0..G9# (108 Words)

SongStart:
  SONGCHANA: // PSG Channel A Tone Song Data At 250ms (15 VSYNCS)
    db C5, REST, C5, REST, G5, REST, G5, REST, A5, REST, A5, REST, G5, SUST, SUST, REST // 1. Twinkle Twinkle Little Star...
    db F5, REST, F5, REST, E5, REST, E5, REST, D5, REST, D5, REST, C5, SUST, SUST, REST // 2.   How I Wonder What You Are...
    db G5, REST, G5, REST, F5, REST, F5, REST, E5, REST, E5, REST, D5, SUST, SUST, REST // 3.  Up Above The World So High...
    db G5, REST, G5, REST, F5, REST, F5, REST, E5, REST, E5, REST, D5, SUST, SUST, REST // 4.   Like A Diamond In The Sky...
    db C5, REST, C5, REST, G5, REST, G5, REST, A5, REST, A5, REST, G5, SUST, SUST, REST // 5. Twinkle Twinkle Little Star...
    db F5, REST, F5, REST, E5, REST, E5, REST, D5, REST, D5, REST, C5, SUST, SUST, REST // 6.   How I Wonder What You Are...
SongEnd: