// MSX Turbo-R CPU R800 ROM Mode demo by krom (Peter Lemon):
arch msxtr.cpu
output "R800ROM.rom", create
fill $8000 // Set ROM Size (32KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB/MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB/MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  ld hl,CHMSG // HL = Character Message Address

PrintLoop:
  ld a,(hl) // A = Character
  or a // A |= A
  jp z,CPUMode // IF (Character == Zero) Finish Printing
  call CHPUT // CALL System Routine To Display A Character To The Screen
  inc hl // Character Message Address++
  jr PrintLoop // Continue Printing

CPUMode: // Change CPU Mode To R800 ROM Mode
  ld a,%10000001 // A = Settings: %L00000MM - L = LED (1 = Switched On With CPU Mode), M = CPU Mode (1 = R800 ROM Mode)
  call CHGCPU // CALL System Routine To Change CPU Mode

Loop:
  jr Loop

CHMSG:
  db 13,"\nMSX Turbo-R CPU R800 ROM Mode\n\n" // Text (Null-Terminated String)
  db 13,"CPU Mode Set To R800 ROM Mode\n\n"
  db 13,"TURBO LED Switched On",0