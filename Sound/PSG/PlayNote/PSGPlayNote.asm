// MSX AY8910 PSG Play Note demo by krom (Peter Lemon):
arch msx.cpu
output "PSGPlayNote.rom", create
fill $8000 // Set ROM Size (32KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB/MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB/MSX_SYSTEM.INC" // Include MSX System Routines
include "LIB/MSX_PSG.INC"    // Include MSX PSG Definitions

Start:

// Play Note On Tone Channel A
ld a,PSG_FINE_TUNE_A // A = PSG Channel A Fine Tune Address ($00)
ld e,0               // E = PSG Channel A Fine Tune (Bits 0..7 Fine Tune = 0)
call WRTPSG          // PSG Write Data (A = PSG Address, E = PSG Data)

ld a,PSG_COARSE_TUNE_A // A = PSG Channel A Course Tune Address ($01)
ld e,1                 // E = PSG Channel A Coarse Tune (Bits 0..3 Course Tune = 1)
call WRTPSG            // PSG Write Data (A = PSG Address, E = PSG Data)

ld a,PSG_MODE_VOL_A // A = PSG Channel A Mode/Volume Address ($08)
ld e,15             // E = PSG Channel A Mode/Volume (Bit 4 Mode = 0, Bits 0..3 Volume = 15)
call WRTPSG         // PSG Write Data (A = PSG Address, E = PSG Data)

ld a,PSG_KEY   // A = PSG Channel Enable Address ($07)
ld e,%00111110 // E = PSG Channel A Tone Enable (Bits 6..7 Port A/B Mode, Bits 3..5 Channel A..C Enable Noise, Bits 0..2 Channel A..C Enable Tone)
call WRTPSG    // PSG Write Data (A = PSG Address, E = PSG Data)

Loop:
  jr Loop