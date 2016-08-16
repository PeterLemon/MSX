// MSX "Hello, World!" Text Printing demo by krom (Peter Lemon):
arch msx.cpu
output "HelloWorld.rom", create
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
  jp z,Loop // IF (Character == Zero) Finish Printing
  call CHPUT // CALL System Routine To Display A Character To The Screen
  inc hl // Character Message Address++
  jr PrintLoop // Continue Printing

Loop:
  jr Loop

CHMSG:
  db 13,"\nHello, World!",0 // Hello World Text (Null-Terminated String)