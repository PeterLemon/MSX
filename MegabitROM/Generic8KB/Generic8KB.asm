// MSX Megabit ROM Generic (8KB Banks) demo by krom (Peter Lemon):
arch msx.cpu
output "Generic8KB.rom", create
fill $40000 // Set ROM Size (256KB)

origin $0000
base $4000 // Entry Point Of Code
include "LIB/MSX_HEADER.ASM" // Include MSX ROM Header
include "LIB/MSX_SYSTEM.INC" // Include MSX System Routines

Start:
  ld hl,BANK0MSG // HL = Character Message Address

PrintLoop0:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start1   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop0 // Continue Printing


Start1:
  ld a,1         // A = Bank 1
  ld ($6000),a   // Store Bank 1
  ld hl,BANK1MSG // HL = Character Message Address

PrintLoop1:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start2   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop1 // Continue Printing


Start2:
  ld a,2         // A = Bank 2
  ld ($6000),a   // Store Bank 2
  ld hl,BANK2MSG // HL = Character Message Address

PrintLoop2:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start3   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop2 // Continue Printing


Start3:
  ld a,3         // A = Bank 3
  ld ($6000),a   // Store Bank 3
  ld hl,BANK3MSG // HL = Character Message Address

PrintLoop3:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start4   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop3 // Continue Printing


Start4:
  ld a,4         // A = Bank 4
  ld ($6000),a   // Store Bank 4
  ld hl,BANK4MSG // HL = Character Message Address

PrintLoop4:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start5   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop4 // Continue Printing


Start5:
  ld a,5         // A = Bank 5
  ld ($6000),a   // Store Bank 5
  ld hl,BANK5MSG // HL = Character Message Address

PrintLoop5:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start6   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop5 // Continue Printing


Start6:
  ld a,6         // A = Bank 6
  ld ($6000),a   // Store Bank 6
  ld hl,BANK6MSG // HL = Character Message Address

PrintLoop6:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start7   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop6 // Continue Printing


Start7:
  ld a,7         // A = Bank 7
  ld ($6000),a   // Store Bank 7
  ld hl,BANK7MSG // HL = Character Message Address

PrintLoop7:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start8   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop7 // Continue Printing


Start8:
  ld a,8         // A = Bank 8
  ld ($6000),a   // Store Bank 8
  ld hl,BANK8MSG // HL = Character Message Address

PrintLoop8:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start9   // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop8 // Continue Printing


Start9:
  ld a,9         // A = Bank 9
  ld ($6000),a   // Store Bank 9
  ld hl,BANK9MSG // HL = Character Message Address

PrintLoop9:
  ld a,(hl)     // A = Character
  or a          // A |= A
  jp z,Start10  // IF (Character == Zero) Finish Printing
  call CHPUT    // CALL System Routine To Display A Character To The Screen
  inc hl        // Character Message Address++
  jr PrintLoop9 // Continue Printing


Start10:
  ld a,10         // A = Bank 10
  ld ($6000),a    // Store Bank 10
  ld hl,BANK10MSG // HL = Character Message Address

PrintLoop10:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start11   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop10 // Continue Printing


Start11:
  ld a,11         // A = Bank 11
  ld ($6000),a    // Store Bank 11
  ld hl,BANK11MSG // HL = Character Message Address

PrintLoop11:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start12   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop11 // Continue Printing


Start12:
  ld a,12         // A = Bank 12
  ld ($6000),a    // Store Bank 12
  ld hl,BANK12MSG // HL = Character Message Address

PrintLoop12:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start13   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop12 // Continue Printing


Start13:
  ld a,13         // A = Bank 13
  ld ($6000),a    // Store Bank 13
  ld hl,BANK13MSG // HL = Character Message Address

PrintLoop13:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start14   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop13 // Continue Printing


Start14:
  ld a,14         // A = Bank 14
  ld ($6000),a    // Store Bank 14
  ld hl,BANK14MSG // HL = Character Message Address

PrintLoop14:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start15   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop14 // Continue Printing


Start15:
  ld a,15         // A = Bank 15
  ld ($6000),a    // Store Bank 15
  ld hl,BANK15MSG // HL = Character Message Address

PrintLoop15:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start16   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop15 // Continue Printing


Start16:
  ld a,16         // A = Bank 16
  ld ($6000),a    // Store Bank 16
  ld hl,BANK16MSG // HL = Character Message Address

PrintLoop16:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start17   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop16 // Continue Printing


Start17:
  ld a,17         // A = Bank 17
  ld ($6000),a    // Store Bank 17
  ld hl,BANK17MSG // HL = Character Message Address

PrintLoop17:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start18   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop17 // Continue Printing


Start18:
  ld a,18         // A = Bank 18
  ld ($6000),a    // Store Bank 18
  ld hl,BANK18MSG // HL = Character Message Address

PrintLoop18:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start19   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop18 // Continue Printing


Start19:
  ld a,19         // A = Bank 19
  ld ($6000),a    // Store Bank 19
  ld hl,BANK19MSG // HL = Character Message Address

PrintLoop19:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start20   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop19 // Continue Printing


Start20:
  ld a,20         // A = Bank 20
  ld ($6000),a    // Store Bank 20
  ld hl,BANK20MSG // HL = Character Message Address

PrintLoop20:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start21   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop20 // Continue Printing


Start21:
  ld a,21         // A = Bank 21
  ld ($6000),a    // Store Bank 21
  ld hl,BANK21MSG // HL = Character Message Address

PrintLoop21:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start22   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop21 // Continue Printing


Start22:
  ld a,22         // A = Bank 22
  ld ($6000),a    // Store Bank 22
  ld hl,BANK22MSG // HL = Character Message Address

PrintLoop22:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start23   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop22 // Continue Printing


Start23:
  ld a,23         // A = Bank 23
  ld ($6000),a    // Store Bank 23
  ld hl,BANK23MSG // HL = Character Message Address

PrintLoop23:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start24   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop23 // Continue Printing


Start24:
  ld a,24         // A = Bank 24
  ld ($6000),a    // Store Bank 24
  ld hl,BANK24MSG // HL = Character Message Address

PrintLoop24:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start25   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop24 // Continue Printing


Start25:
  ld a,25         // A = Bank 25
  ld ($6000),a    // Store Bank 25
  ld hl,BANK25MSG // HL = Character Message Address

PrintLoop25:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start26   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop25 // Continue Printing


Start26:
  ld a,26         // A = Bank 26
  ld ($6000),a    // Store Bank 26
  ld hl,BANK26MSG // HL = Character Message Address

PrintLoop26:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start27   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop26 // Continue Printing


Start27:
  ld a,27         // A = Bank 27
  ld ($6000),a    // Store Bank 27
  ld hl,BANK27MSG // HL = Character Message Address

PrintLoop27:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start28   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop27 // Continue Printing


Start28:
  ld a,28         // A = Bank 28
  ld ($6000),a    // Store Bank 28
  ld hl,BANK28MSG // HL = Character Message Address

PrintLoop28:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start29   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop28 // Continue Printing


Start29:
  ld a,29         // A = Bank 29
  ld ($6000),a    // Store Bank 29
  ld hl,BANK29MSG // HL = Character Message Address

PrintLoop29:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start30   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop29 // Continue Printing


Start30:
  ld a,30         // A = Bank 30
  ld ($6000),a    // Store Bank 30
  ld hl,BANK30MSG // HL = Character Message Address

PrintLoop30:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Start31   // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop30 // Continue Printing


Start31:
  ld a,31         // A = Bank 31
  ld ($6000),a    // Store Bank 31
  ld hl,BANK31MSG // HL = Character Message Address

PrintLoop31:
  ld a,(hl)      // A = Character
  or a           // A |= A
  jp z,Loop      // IF (Character == Zero) Finish Printing
  call CHPUT     // CALL System Routine To Display A Character To The Screen
  inc hl         // Character Message Address++
  jr PrintLoop31 // Continue Printing


Loop:
  jr Loop

BANK0MSG:
  db 14,"\nBANK 0        ",0 // Bank 0 Text (Null-Terminated String)

// BANK 1
origin $02000
base $6000
BANK1MSG:
  db 14,"BANK 1         ",0 // Bank 1 Text (Null-Terminated String)

// BANK 2
origin $04000
base $6000
BANK2MSG:
  db 13,"BANK 2        ",0 // Bank 2 Text (Null-Terminated String)

// BANK 3
origin $06000
base $6000
BANK3MSG:
  db 14,"BANK 3         ",0 // Bank 3 Text (Null-Terminated String)

// BANK 4
origin $08000
base $6000
BANK4MSG:
  db 13,"BANK 4        ",0 // Bank 4 Text (Null-Terminated String)

// BANK 5
origin $0A000
base $6000
BANK5MSG:
  db 14,"BANK 5         ",0 // Bank 5 Text (Null-Terminated String)

// BANK 6
origin $0C000
base $6000
BANK6MSG:
  db 13,"BANK 6        ",0 // Bank 6 Text (Null-Terminated String)

// BANK 7
origin $0E000
base $6000
BANK7MSG:
  db 14,"BANK 7         ",0 // Bank 7 Text (Null-Terminated String)

// BANK 8
origin $10000
base $6000
BANK8MSG:
  db 13,"BANK 8        ",0 // Bank 8 Text (Null-Terminated String)

// BANK 9
origin $12000
base $6000
BANK9MSG:
  db 14,"BANK 9         ",0 // Bank 9 Text (Null-Terminated String)

// BANK 10
origin $14000
base $6000
BANK10MSG:
  db 13,"BANK 10       ",0 // Bank 10 Text (Null-Terminated String)

// BANK 11
origin $16000
base $6000
BANK11MSG:
  db 14,"BANK 11        ",0 // Bank 11 Text (Null-Terminated String)

// BANK 12
origin $18000
base $6000
BANK12MSG:
  db 13,"BANK 12       ",0 // Bank 12 Text (Null-Terminated String)

// BANK 13
origin $1A000
base $6000
BANK13MSG:
  db 14,"BANK 13        ",0 // Bank 13 Text (Null-Terminated String)

// BANK 14
origin $1C000
base $6000
BANK14MSG:
  db 13,"BANK 14       ",0 // Bank 14 Text (Null-Terminated String)

// BANK 15
origin $1E000
base $6000
BANK15MSG:
  db 14,"BANK 15        ",0 // Bank 15 Text (Null-Terminated String)

// BANK 16
origin $20000
base $6000
BANK16MSG:
  db 13,"BANK 16       ",0 // Bank 16 Text (Null-Terminated String)

// BANK 17
origin $22000
base $6000
BANK17MSG:
  db 14,"BANK 17        ",0 // Bank 17 Text (Null-Terminated String)

// BANK 18
origin $24000
base $6000
BANK18MSG:
  db 13,"BANK 18       ",0 // Bank 18 Text (Null-Terminated String)

// BANK 19
origin $26000
base $6000
BANK19MSG:
  db 14,"BANK 19        ",0 // Bank 19 Text (Null-Terminated String)

// BANK 20
origin $28000
base $6000
BANK20MSG:
  db 13,"BANK 20       ",0 // Bank 20 Text (Null-Terminated String)

// BANK 21
origin $2A000
base $6000
BANK21MSG:
  db 14,"BANK 21        ",0 // Bank 21 Text (Null-Terminated String)

// BANK 22
origin $2C000
base $6000
BANK22MSG:
  db 13,"BANK 22       ",0 // Bank 22 Text (Null-Terminated String)

// BANK 23
origin $2E000
base $6000
BANK23MSG:
  db 14,"BANK 23        ",0 // Bank 23 Text (Null-Terminated String)

// BANK 24
origin $30000
base $6000
BANK24MSG:
  db 13,"BANK 24       ",0 // Bank 24 Text (Null-Terminated String)

// BANK 25
origin $32000
base $6000
BANK25MSG:
  db 14,"BANK 25        ",0 // Bank 25 Text (Null-Terminated String)

// BANK 26
origin $34000
base $6000
BANK26MSG:
  db 13,"BANK 26       ",0 // Bank 26 Text (Null-Terminated String)

// BANK 27
origin $36000
base $6000
BANK27MSG:
  db 14,"BANK 27        ",0 // Bank 27 Text (Null-Terminated String)

// BANK 28
origin $38000
base $6000
BANK28MSG:
  db 13,"BANK 28       ",0 // Bank 28 Text (Null-Terminated String)

// BANK 29
origin $3A000
base $6000
BANK29MSG:
  db 14,"BANK 29        ",0 // Bank 29 Text (Null-Terminated String)

// BANK 30
origin $3C000
base $6000
BANK30MSG:
  db 13,"BANK 30       ",0 // Bank 30 Text (Null-Terminated String)

// BANK 31
origin $3E000
base $6000
BANK31MSG:
  db 14,"BANK 31        ",0 // Bank 31 Text (Null-Terminated String)