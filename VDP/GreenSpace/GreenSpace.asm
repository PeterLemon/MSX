// MSX Green Space Demo by krom (Peter Lemon):
arch msx.cpu
output "GreenSpace.rom", create
fill $8000 // Set ROM Size (32KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB/MSX.INC"        // Include MSX Definitions
include "LIB/MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB/MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  // Set Screen Mode 0
  ld a,0 // A = Screen Mode 0
  call CHGMOD // CALL System Routine To Change Screen Mode

  // Change Screen Color
  ld a,$02      // A = Palette Entry #2 (Green)
  ld (FORCLR),a // FORCLR ($F3E9) Foreground Color = A
  ld a,$02      // A = Palette Entry #2 (Green)
  ld (BAKCLR),a // BAKCLR ($F3EA) Background Color = A
  ld a,$02      // A = Palette Entry #2 (Green)
  ld (BDRCLR),a // BDRCLR ($F3EB) Border Color = A
  ld a,0 // A = Screen Mode 0
  call CHGCLR // CALL System Routine To Change Screen Color

Loop:
  jr Loop