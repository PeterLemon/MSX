//=====================
// MSX System Routines
//=====================
// BIOS LISTING
// This Section Lists BIOS Entries Available To The User
// There Are 2 Kinds Of BIOS Routines: "MAIN-ROM" & "SUB-ROM"
// Routines In MAIN-ROM Use "CALL" Or "RTS" Instruction As A Subroutine Call
// The Call Sequence Of SUB-ROM Is As Follows:
//
// LD IX,INIPLT ; Set BIOS Entry Address
// CALL EXTROM  ; Returns here
//
// When Contents Of IX Should Not Be Destroyed:
//
// INIPAL:
//   PUSH IX      ; Save IX
//   LD IX,INIPLT ; Set BIOS Entry Address
//   JP SUBROM    ; Return Caller Of INIPAL

//==========
// MAIN-ROM
//==========

//======
// RSTs
//======
constant CHKRAM($0000) //  Function: Test RAM & Set RAM Slot For The System
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant SYNCHR($0008) //  Function: Test IF Character In [HL] Is Specified
                       //            IF TRUE GOTO CHRGTR ($0010), ELSE Generate SYNTAX ERROR 
                       //     Input: [HL] = Test Character
                       //            Compared Character Is Placed Next To Called RST Instruction
                       //    Output: HL++, A = [HL], CY-Flag Set IF Tested Character Is Numerical
                       //            Z-Flag Set IF At End Of Statement ($00 Or $3A)
                       // Registers: AF, HL
                       // Available: MSX

constant  RDSLT($000C) //  Function: Selects Slot Corresponding To Value In A & Read 1 Byte From Slot Memory
                       //            When Routine Is Called, Interrupt Is Inhibited Even After Execution Ends
                       //     Input:  A = Slot Number: %F000EEBB - F = BASIC(0) Expansion(1),
                       //            EE = Expansion Slot Number(0..3), BB = BASIC Slot Number(0..3)
                       //            HL = Address Of Memory To Be Read
                       //    Output: Value Of Memory Read From A
                       // Registers: AF, BC, DE
                       // Available: MSX

constant CHRGTR($0010) //  Function: Get A Character (Or Token) From BASIC Text
                       //     Input: [HL] = Character To Be Read
                       //    Output: HL++, A = [HL], CY-Flag Set IF Tested Character Is Numerical
                       //            Z-Flag Set IF At End Of Statement ($00 Or $3A)
                       // Registers: AF, HL
                       // Available: MSX

constant  WRSLT($0014) //  Function: Select Slot Corresponding To Value In A & Write 1 Byte To Slot Memory
                       //            When Routine Is Called, Interrupt Is Inhibited Even After Execution Ends
                       //     Input:  A = Slot Number: %F000EEBB - F = BASIC(0) Expansion(1),
                       //            EE = Expansion Slot Number(0..3), BB = BASIC Slot Number(0..3)
                       //            HL = Address Of Memory To Be Read
                       //    Output: NONE
                       // Registers: AF, BC, D
                       // Available: MSX

constant  OUTDO($0018) //  Function: Send Value To Current Device
                       //     Input: A = Value To Be Sent
                       //            Send Output To Printer When PTRFLG ($F416) Is Not Zero
                       //            Send Output To File Specified By PTRFIL ($F864) IF PTRFIL Not Zero
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX (Call SUB-ROM Internally In Screen Modes 5..8)

constant CALSLT($001C) //  Function: Call Routine In Another Slot (Inter-Slot Call)
                       //     Input: IYH = Slot Number: %F000EEBB - F = BASIC(0) Expansion(1),
                       //             EE = Expansion Slot Number(0..3), BB = BASIC Slot Number(0..3)
                       //             IX = Address To Be Called
                       //    Output: Depends On Called Routine
                       // Registers: Depends On Called Routine
                       // Available: MSX

constant DCOMPR($0020) //  Function: Compare Contents Of HL & DE
                       //     Input: HL, DE
                       //    Output: Set Z-Flag IF (HL == DE), Set CY-Flag IF (HL < DE)
                       // Registers: AF
                       // Available: MSX

constant ENASLT($0024) //  Function: Select Slot Corresponding To Value In A & Enable Slot To Be Used
                       //            When Routine Is Called, Interrupt Is Inhibited Even After Execution Ends
                       //     Input:  A = Slot Number: %F000EEBB - F = BASIC(0) Expansion(1),
                       //            EE = Expansion Slot Number(0..3), BB = BASIC Slot Number(0..3)
                       //            HL = Slot Page: 2 High Order Bits
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant GETYPR($0028) //  Function: Return Type Of DAC (Decimal Accumulator)
                       //     Input: NONE
                       //    Output: S, Z, P/V Flags Change Depending On Type Of DAC:
                       //            Types Can Be Recognised By Flag Marked By "*"
                       //            Integer: C = 1,  S = 1*, Z = 0,  P/V = 1
                       //             String: C = 1,  S = 0,  Z = 1*, P/V = 1
                       //             Single: C = 1,  S = 0,  Z = 0,  P/V = 0*
                       //             Double: C = 0*, S = 0,  Z = 0,  P/V = 1
                       // Registers: AF
                       // Available: MSX

constant  CALLF($0030) //  Function: Call Routine In Another Slot
                       //            The Following Is The Call Sequence:
                       //            RST 30H
                       //            DB	n	; n Is The Slot Number (Aame As RDSLT)
                       //            DW	nn	; nn Is The Called Address
                       //     Input: The Method Described Above
                       //    Output: Depends On Called Routine
                       // Registers: AF, Other Registers Depend On Called Routine
                       // Available: MSX

constant KEYINT($0038) //  Function: Executes Timer Interrupt Process Routine
                       //     Input: NONE
                       //    Output: NONE
                       //  Register: NONE
                       // Available: MSX

//====================
// I/O Initialisation
//====================
constant INITIO($003B) //  Function: Initialise I/O Device
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant INIFNK($003E) //  Function: Initialise Contents Of Function Keys
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

//============
// VDP Access
//============
constant DISSCR($0041) //  Function: Disable Screen Display
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: AF, BC
                       // Available: MSX

constant ENASCR($0044) //  Function: Enable Screen Display
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant WRTVDP($0047) //  Function: Write Data To VDP Register
                       //     Input: C = VDP Register Number (0..23, 32..46), B = Data To Write
                       //    Output: NONE
                       // Registers: AF, BC
                       // Available: MSX (Call SUB-ROM Internally In Screen Modes 5..8)

constant  RDVRM($004A) //  Function: Read Data From VRAM (14-Bit Address: $0000..$3FFF) (TMS9918)
                       //            Only Lowest 14-Bits Of VRAM Address Are Valid
                       //            Call NRDVRM To Use All Bits
                       //     Input: HL = VRAM Address To Be Read
                       //    Output:  A = Data Which Was Read
                       // Registers: AF
                       // Available: MSX

constant WRTVRM($004D) //  Function: Write Data To VRAM (14-Bit Address: $0000..$3FFF) (TMS9918)
                       //            Only Lowest 14-Bits Of VRAM Address Are Valid
                       //            Call NWRVRM To Use All 16-Bits
                       //     Input: HL = VRAM Address, A = Data To Write
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant  SETRD($0050) //  Function: Set VRAM (14-Bit Address: $0000..$3FFF) In VDP & Enable It To Be Read (TMS9918)
                       //            This Is Used To Read Auto-Increment Data From VRAM
                       //            Enables Faster Readout Than Using RDVRM In A Loop
                       //            Only Lowest 14-Bits Of VRAM Address Are Valid
                       //            Call NSETRD To Use All Bits
                       //     Input: HL = VRAM Address
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant SETWRT($0053) //  Function: Set VRAM (14-Bit Address: $0000..$3FFF) In VDP & Enable It To Be Written (TMS9918)
                       //            This Is Used To Read Auto-Increment Data From VRAM
                       //            Enables Faster Readout Than Using WRTVRM In A Loop
                       //            Only Lowest 14-Bits Of VRAM Address Are Valid
                       //            Call NSTWRT To Use All Bits
                       //     Input: HL = VRAM Address
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant FILVRM($0056) //  Function: Fill Specified VRAM Area (14-Bit Address: $0000..$3FFF) With Repeated Data (TMS9918)
                       //            Only Lowest 14-Bits Of VRAM Address Are Valid
                       //            Call BIGFIL To Use All Bits
                       //     Input: HL = VRAM Destination Address, BC = Data Length, A = Data To Repeat
                       //    Output: NONE
                       // Registers: AF, BC
                       // Available: MSX (Do Not Call SUB-ROM While Screen Modes 4..8 Are Changed)

constant LDIRMV($0059) //  Function: Block Transfer From VRAM To Memory
                       //     Input: HL = VRAM Source Address, DE = Memory Destination Address, BC = Data Length
                       //            All Bits Of VRAM Address Are Valid
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Do Not Call SUB-ROM While Screen Modes 4..8 Are Changed)

constant LDIRVM($005C) //  Function: Block Transfer From Memory To VRAM
                       //     Input: HL = Memory Source Address, DE = VRAM Destination Address, BC = Data Length
                       //            All Bits Of VRAM Address Are Valid
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Do Not Call SUB-ROM While Screen Modes 4..8 Are Changed)

constant CHGMOD($005F) //  Function: Change Screen Mode
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call CHGMDP In SUB-ROM After This Call
                       //     Input: A = Screen Mode (0..8)
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant CHGCLR($0062) //  Function: Change Screen Color
                       //     Input: A = Screen Mode
                       //            FORCLR ($F3E9) Foreground Color
                       //            BAKCLR ($F3EA) Background Color
                       //            BDRCLR ($F3EB) Border Color
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant    NMI($0066) //  Function: Execute NMI (Non-Maskable Interrupt) Handling Routine
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant CLRSPR($0069) //  Function: Initialise All Sprites
                       //            Sprite Pattern Cleared To Zero, Sprite Number To Sprite Plane Number
                       //            Sprite Color To Foreground Color
                       //            Sprite Vertical Location Set To 209 (Mode 0..3) Or 217 (Mode 4..8)
                       //     Input: SCRMOD ($FCAF) = Screen Mode
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant INITXT($006C) //  Function: Initialise Screen To TEXT1 Mode (40x24)
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: TXTNAM ($F3B3) = Pattern Name Table
                       //            TXTCGP ($F3B7) = Pattern Generator Table
                       //            LINL40 ($F3AE) = Line Length
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant INIT32($006F) //  Function: Initialise Screen To GRAPHIC1 Mode (32x24)
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: T32NAM ($F3BD) = Pattern Name Table
                       //            T32COL ($F3BF) = Color Table
                       //            T32CGP ($F3C1) = Pattern Generator Table
                       //            T32ATR ($F3C3) = Sprite Attribute Table
                       //            T32PAT ($F3C5) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant INIGRP($0072) //  Function: Initialise Screen To High-Resolution Graphics Mode
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: GRPNAM ($F3C7) = Pattern Name Table
                       //            GRPCOL ($F3C9) = Color Table
                       //            GRPCGP ($F3CB) = Pattern Generator Table
                       //            GRPATR ($F3CD) = Sprite Attribute Table
                       //            GRPPAT ($F3CF) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant INIMLT($0075) //  Function: Initialise Screen To MULTI COLOR Mode
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: MLTNAM ($F3D1) = Pattern Name Table
                       //            MLTCOL ($F3D3) = Color Table
                       //            MLTCGP ($F3D5) = Pattern Generator Table
                       //            MLTATR ($F3D7) = Sprite Attribute Table
                       //            MLTPAT ($F3D9) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant SETTXT($0078) //  Function: Set Only VDP To TEXT1 Mode (40x24)
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: TXTNAM ($F3B3) = Pattern Name Table
                       //            TXTCGP ($F3B7) = Pattern Generator Table
                       //            LINL40 ($F3AE) = Line Length
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant SETT32($007B) //  Function: Set Only VDP To GRAPHIC1 Mode (32x24)
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: T32NAM ($F3BD) = Pattern Name Table
                       //            T32COL ($F3BF) = Color Table
                       //            T32CGP ($F3C1) = Pattern Generator Table
                       //            T32ATR ($F3C3) = Sprite Attribute Table
                       //            T32PAT ($F3C5) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant SETGRP($007E) //  Function: Set Only VDP To GRAPHIC2 Mode
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: GRPNAM ($F3C7) = Pattern Name Table
                       //            GRPCOL ($F3C9) = Color Table
                       //            GRPCGP ($F3CB) = Pattern Generator Table
                       //            GRPATR ($F3CD) = Sprite Attribute Table
                       //            GRPPAT ($F3CF) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant SETMLT($0081) //  Function: Set Only VDP To MULTI COLOR Mode
                       //            Palette Is Not Initialised
                       //            To Initialise Palette Call INIPLT In SUB-ROM After This Call
                       //     Input: MLTNAM ($F3D1) = Pattern Name Table
                       //            MLTCOL ($F3D3) = Color Table
                       //            MLTCGP ($F3D5) = Pattern Generator Table
                       //            MLTATR ($F3D7) = Sprite Attribute Table
                       //            MLTPAT ($F3D9) = Sprite Generator Table
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant CALPAT($0084) //  Function: Return Address Of Sprite Generator Table
                       //     Input:  A = Sprite Number
                       //    Output: HL = Returned Address
                       // Registers: AF, DE, HL
                       // Available: MSX

constant CALATR($0087) //  Function: Return Address Of Sprite Attribute Table
                       //     Input:  A = Sprite Number
                       //    Output: HL = Returned Address
                       // Registers: AF, DE, HL
                       // Available: MSX

constant GSPSIZ($008A) //  Function: Return Current Sprite Size
                       //     Input: NONE
                       //    Output: A = Sprite Size (In Bytes)
                       //            CY-Flag Set IF (Size == 16x16), ELSE CY-Flag Reset
                       // Registers: AF
                       // Available: MSX

constant GRPPRT($008D) //  Function: Display A Character On The Graphic-Screen
                       //     Input: A = Character Code To Be Displayed
                       //            Set Logical Operation Code In LOGOPR ($FB02) IF Screen Mode 0..8
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX (Call SUB-ROM Internally In Screen Modes 5..8)

//=====
// PSG
//=====
constant GICINI($0090) //  Function: Initialise PSG & Set Initial Value For PLAY Statement
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant WRTPSG($0093) //  Function: Write Data To PSG Register
                       //     Input: A = PSG Register Number, E = Data To Write
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant  RDPSG($0096) //  Function: Read PSG Register Data
                       //     Input: A = PSG Register Number
                       //    Output: A = Data Which Was Read
                       // Registers: NONE
                       // Available: MSX

constant STRTMS($0099) //  Function: Test IF The PLAY Statement Is Being Executed As A Background Task
                       //            IF Not, Begin To Execute The PLAY Statement
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

//=====================================
// Keyboard, CRT, Printer Input-Output
//=====================================
constant  CHSNS($009C) //  Function: Test Status Of Keyboard Buffer
                       //     Input: NONE
                       //    Output: Z-Flag Set IF Buffer Is Empty, ELSE Z-Flag Reset
                       // Registers: AF
                       // Available: MSX

constant  CHGET($009F) //  Function: Get Character Input (Waiting)
                       //     Input: NONE
                       //    Output: A = Code Of Input Character
                       // Registers: AF
                       // Available: MSX

constant  CHPUT($00A2) //  Function: Display A Character To The Screen
                       //     Input: A = Character Code To Be Displayed
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant LPTOUT($00A5) //  Function: Send A Character To The Printer
                       //     Input: A = Character Code To Be Sent
                       //    Output: IF Failed CY-Flag Set, ELSE CY-Flag Reset
                       // Registers: F
                       // Available: MSX

constant LPTSTT($00A8) //  Function: Test Printer Status
                       //     Input: NONE
                       //    Output: IF (A == 255) && (Z-Flag Reset), Printer Is READY
                       //            IF (A == 0) && (Z-Flag Set), Printer Is NOT READY
                       // Registers: AF
                       // Available: MSX

constant CNVCHR($00AB) //  Function: Test Graphic Header & Transform The Code
                       //     Input: A = Character Code
                       //    Output: IF NOT Graphic Header CY-Flag Reset
                       //            CY-Flag Set, & Z-Flag Set To The Transformed Code Set In A
                       //            CY-Flag Set, & CY-Flag is Reset To The Utransformed Code Set In A
                       // Registers: AF
                       // Available: MSX

constant PINLIN($00AE) //  Function: Store To Specified Buffer Character Code Input Until RETURN Or STOP Key Pressed
                       //     Input: NONE
                       //    Output: HL = Start Address Of Buffer -1
                       //            CY-Flag Set IF STOP Key Pressed
                       // Registers: ALL
                       // Available: MSX

constant  INLIN($00B1) //  Function: Store To Specified Buffer Character Code Input Until RETURN Or STOP Key Pressed
                       //     Input: NONE
                       //    Output: HL = Start Address Of Buffer -1
                       //            CY-Flag Set IF STOP Key Pressed
                       //            AUTFLG ($F6AA) Set
                       // Registers: ALL
                       // Available: MSX

constant QINLIN($00B4) //  Function: Store To Specified Buffer Character Code Input Until RETURN Or STOP Key Pressed
                       //            Displays A Question Mark "?" & A Single Space " "
                       //     Input: NONE
                       //    Output: HL = Start Address Of Buffer -1
                       //            CY-Flag Set IF STOP Key Pressed
                       //            AUTFLG ($F6AA) Set
                       // Registers: ALL
                       // Available: MSX

constant BREAKX($00B7) //  Function: Test CTRL-STOP Key, Interrupts Are Inhibited
                       //     Input: NONE
                       //    Output: CY-Flag Set IF CTRL-STOP Key Pressed
                       // Registers: AF
                       // Available: MSX

constant ISCNTC($00BA) //  Function: Test SHIFT-STOP Key, Interrupts Are Inhibited
                       //     Input: NONE
                       //    Output: CY-Flag Set IF SHIFT-STOP Key Pressed
                       // Registers: AF
                       // Available: MSX

constant CKCNTC($00BD) //  Function: Test SHIFT-STOP Key, Interrupts Are Inhibited (Same As ISCNTC, Used In BASIC)
                       //     Input: NONE
                       //    Output: CY-Flag Set IF SHIFT-STOP Key Pressed
                       // Registers: AF
                       // Available: MSX

constant   BEEP($00C0) //  Function: Generate BEEP
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Always Call SUB-ROM)

constant    CLS($00C3) //  Function: Clear Screen
                       //     Input: Set Z-Flag (e.g XOR A)
                       //    Output: NONE
                       // Registers: AF, BC, DE
                       // Available: MSX (Always Call SUB-ROM)

constant  POSIT($00C6) //  Function: Move Cursor
                       //     Input: H = X-Position Of Cursor, L = Y-Position Of Cursor
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant  FNKSB($00C9) //  Function: Test Whether Function Key Display Is Active (FNKFLG)
		       //            IF TRUE, Display Them, ELSE Erase Them
                       //     Input: FNKFLG ($FBCE)
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant ERAFNK($00CC) //  Function: Erase Function Key Display
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

constant DSPFNK($00CF) //  Function: Display Function Keys
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (Call SUB-ROM Internally In Screen Modes 5..8)

constant TOTEXT($00D2) //  Function: Force Screen To Text Mode
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX

//=================
// Game I/O Access
//=================
constant GTSTCK($00D5) //  Function: Return Joystick Direction Status
                       //     Input: A = Joystick Number To Test
                       //    Output: A = Joystick Direction Status
                       // Registers: ALL
                       // Available: MSX

constant GTTRIG($00D8) //  Function: Return Trigger Button Status
                       //     Input: A = Trigger Button Number To Test
                       //    Output: IF (A == $00) Trigger Button Is Not Pressed
		       //            IF (A == $FF) Trigger Button Is Pressed
                       // Registers: AF
                       // Available: MSX

constant  GTPAD($00DB) //  Function: Return Touch Pad Status
                       //     Input: A = Touch Pad Number To Test
                       //    Output: A = Touch Pad Status
                       // Registers: ALL
                       // Available: MSX

constant  GTPDL($00DE) //  Function: Return Paddle Value
                       //     Input: A = Paddle Number To Test
                       //    Output: A = Paddle Value
                       // Registers: ALL
                       // Available: MSX (Call SUB-ROM Internally In Screen Modes 5..8)

//================================
// Cassette Input-Output Routines
//================================
constant TAPION($00E1) //  Function: Read Header Block After Turning Cassette Motor ON
                       //     Input: NONE
                       //    Output: CY-Flag Set IF Failed
                       // Registers: ALL
                       // Available: MSX

constant  TAPIN($00E4) //  Function: Read Data From Tape
                       //     Input: NONE
                       //    Output: A = Tape Data, CY-Flag Set IF Failed
                       // Registers: ALL
                       // Available: MSX

constant TAPIOF($00E7) //  Function: Stop Reading Data From Tape
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant TAPOON($00EA) //  Function: Write Header Block After Turning Cassette Motor ON
                       //     Input: IF (A == 0) Short Header, IF (A != 0) Long Header
                       //    Output: CY-Flag Set IF Failed
                       // Registers: ALL
                       // Available: MSX

constant TAPOUT($00ED) //  Function: Write Data To Tape
                       //     Input: A = Data To Write
                       //    Output: CY-Flag Set IF Failed
                       // Registers: ALL
                       // Available: MSX

constant TAPOOF($00F0) //  Function: Stop Writing Data To Tape
                       //     Input: A = Data To Write
                       //    Output: CY-Flag Set IF Failed
                       // Registers: ALL
                       // Available: MSX

constant STMOTR($00F3) //  Function: Set Cassette Motor Action
                       //     Input: IF (A == $00) Stop
                       //            IF (A == $01) Start
                       //            IF (A == $FF) Reverse Current Action
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

//================
// Queue Routines
//================
constant   LFTQ($00F6) //  Function: Gives Number Of Bytes In Queue (Internal Use)
                       //     Input: NONE
                       //    Output: A = Length Of Queue In Bytes
                       // Registers: AF
                       // Available: MSX

constant   PUTQ($00F9) //  Function: Put Byte In Queue (Internal Use)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

//==================
// Graphic Routines
//==================
constant RIGHTC($00FC) //  Function: Move Pixel Right
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant  LEFTC($00FF) //  Function: Move Pixel Left
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant    UPC($0102) //  Function: Move Pixel Up
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant   TUPC($0105) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute UPC (Move Pixel Up)
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       //              CY-Flag Set IF Operation Would End Outside Screen Border
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant  DOWNC($0108) //  Function: Move Pixel Down
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant TDOWNC($010B) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute DOWNC (Move Pixel Down)
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       //              CY-Flag Set IF Operation Would End Outside Screen Border
                       // Registers: AF
                       // Available: MSX (SCREEN 3 Only)

constant SCALXY($010E) //  Function: Clip X,Y Coordinates (Against Screen Border)
                       //     Input: BC = X-Coordinate, DE = Y-Coordinate
                       //    Output: BC = X-Coordinate Clipped, DE = Y-Coordinate Clipped
                       // Registers: AF
                       // Available: MSX

constant  MAPXY($0111) //  Function: Place Cursor At Current Cursor Address
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant FETCHC($0114) //  Function: Get Current Cursor Addresses Mask Pattern
                       //     Input: NONE
                       //    Output: HL = Cursor Address
                       //             A = Mask Pattern
                       // Registers: NONE
                       // Available: MSX

constant STOREC($0117) //  Function: Record Current Cursor Addresses Mask Pattern
                       //     Input: HL = Cursor Address
                       //             A = Mask Pattern
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant SETATR($011A) //  Function: Set Attribute Byte In ATRBYT ($F3F2)
                       //     Input: A = Attribute
                       //    Output: CY-Flag Set IF Wrong Attribute
                       // Registers: F
                       // Available: MSX

constant  READC($011D) //  Function: Read Attribute Byte Of Current Screen Pixel
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: A = Pixel Attribute
                       // Registers: AF
                       // Available: MSX

constant   SETC($0120) //  Function: Set Attribute Of Pixel
                       //     Input:   CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //            ATRBYT = Attribute Byte
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant NSETCX($0123) //  Function: Set Horizontal Screen Pixels
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant GTASPC($0126) //  Function: Get Screen Relations
                       //     Input: NONE
                       //    Output: DE, HL
                       // Registers: DE, HL
                       // Available: MSX

constant PNTINI($0129) //  Function: Initalises PAINT Instruction
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant  SCANR($012C) //  Function: Scan Screen Pixels Right
                       //     Input: B = "Suspend" Flag, C = Border-Counting
                       //    Output: C = "Pixel-Changed" Flag, DE = Border-Counting
                       // Registers: ALL
                       // Available: MSX

constant  SCANL($012F) //  Function: Scan Screen Pixels Left
                       //     Input: B = "Suspend" Flag, C = Border-Counting
                       //    Output: C = "Pixel-Changed" Flag, DE = Border-Counting
                       // Registers: ALL
                       // Available: MSX

//===============
// Miscellaneous
//===============
constant CHGCAP($0132) //  Function: Alternate CAP Lamp Status
                       //     Input: IF (A == 0) Lamp OFF, IF (A != 0) Lamp ON
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant CHGSND($0135) //  Function: Alternate 1-Bit Sound Port Status
                       //     Input: IF (A == 0) Sound Port OFF
                       //            IF (A != 0) Sound Port ON
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX

constant RSLREG($0138) //  Function: Read Contents Of Current Output To BASIC Slot Register
                       //     Input: NONE
                       //    Output: A = Value Which Was Read
                       // Registers: A
                       // Available: MSX

constant WSLREG($013B) //  Function: Write To Primary Slot Register
                       //     Input: A = Value To Write
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX

constant  RDVDP($013E) //  Function: Read VDP Status Register
                       //     Input: NONE
                       //    Output: A = Value Which Was Read
                       // Registers: A
                       // Available: MSX

constant SNSMAT($0141) //  Function: Read Data Of Specified Line From Keyboard Matrix
                       //     Input: A = Specified Line
                       //    Output: A = Data Which Was Read (Bit Corresponding To Pressed Key Will Be 0)
                       // Registers: AF, C
                       // Available: MSX

constant PHYDIO($0144) //  Function: Physical Input/Output For DISK Devices
                       //     Input:  A = Drive Number (0 = A:, 1 = B:,...)
                       //             B = Number Of Sector To Be Read From Or Written To
                       //             C = Media ID
                       //            DE = First Sector Number To Be Read From Or Written To
                       //            HL = Starting Address Of RAM Buffer To Be Read From Or Written To Specified Sectors
		       //            CY-Flag Set For Sector Writing, CY-Flag Reset For Sector Reading
                       //    Output: CY-Flag Set IF Failed
                       //             B = Number Of Sectors Actually Read Or Written
                       //             A = Error Code (Only IF CY-Flag Set):
                       //                 0 = Write Protected
                       //                 2 = Not Ready
                       //                 4 = Data Error
                       //                 6 = Seek Error
                       //                 8 = Record Not Found
                       //                10 = Write Error
                       //                12 = Bad Parameter
                       //                14 = Out Of Memory
                       //                16 = Other Error
                       // Registers: ALL
                       // Available: MSX

constant FORMAT($0147) //  Function: Initialises Mass-Storage Media Like Formatting Of Disks
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX (In Minimum Configuration Only A HOOK Is Available)

constant ISFLIO($014A) //  Function: Test Whether Device Is Active
                       //     Input: NONE
                       //    Output: IF (A == 0) Active
                       //            IF (A != 0) Inactive
                       // Registers: AF
                       // Available: MSX

constant OUTDLP($014D) //  Function: Printer Output, Different From LPTOUT In The Following Points:
                       //            1. TAB Is Expanded To Spaces
                       //            2. For Non-MSX Printers, Hiragana Is Transformed To Katakana
                       //               & Graphic Characters Are Transformed To	1-Byte characters
                       //            3. Device I/O Error Occurs IF Failed
                       //     Input: A = Data
                       //    Output: NONE
                       // Registers: F
                       // Available: MSX

constant GETVCP($0150) //  Function: Return Pointer To Play Queue (Only Used To Play Music In Background)
                       //     Input: A = Channel Number
                       //    Output: HL = Pointer
                       // Registers: AF
                       // Available: MSX

constant GETVC2($0153) //  Function: Return Pointer To Variable In Queue Number VOICEN (Byte Op $FB38)
                       //     Input: L = Pointer In Play Buffer
                       //    Output: HL = Pointer
                       // Registers: AF
                       // Available: MSX

constant KILBUF($0156) //  Function: Clear Keyboard Buffer
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: HL
                       // Available: MSX

constant CALBAS($0159) //  Function: Executes Inter-Slot Call To Routine In BASIC Interpreter
                       //     Input: IX = Call Address
                       //    Output: Depends On Called Routine
                       // Registers: Depends On Called Routine
                       // Available: MSX

//===========================
// Entries Appended For MSX2
//===========================
constant SUBROM($015C) //  Function: Execute Inter-Slot Call To SUB-ROM
                       //     Input: IX = Call Address, Pushes IX On Stack
                       //    Output: Depends On Called Routine
                       // Registers: Background Registers & IY Are Reserved
                       // Available: MSX2

constant EXTROM($015F) //  Function: Execute Inter-Slot Call To SUB-ROM
                       //     Input: IX For The Call Address
                       //    Output: Depends On Called Routine
                       // Registers: Background Registers & IY Are Reserved
                       // Available: MSX2

constant CHKSLZ($0162) //  Function: Search Slots For SUB-ROM
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant CHKNEW($0165) //  Function: Test Screen Mode
                       //     Input: NONE
                       //    Output: CY-Flag Set IF Screen Mode = 5, 6, 7 Or 8 
                       // Registers: AF
                       // Available: MSX2

constant    EOL($0168) //  Function: Delete To End Of Line
                       //     Input: H = X-Position Of Cursor, L = Y-Position Of Cursor
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant BIGFIL($016B) //  Function: Same Function As FILVRM, Differences Are As Follows:
                       //            In FILVRM, It Is Tested Whether Screen Mode Is 0..3
                       //            IF TRUE, It Treats VDP As Though It Only Has 16KB VRAM
                       //            (For Compatibility With MSX1)
                       //            In BIGFIL, The Screen Mode Is Not Tested
                       //            & Actions Are Carried Out By Given Parameters
                       //     Input: HL = VRAM Destination Address, BC = Data Length, A = Data To Repeat
                       //    Output: NONE
                       // Registers: AF, BC
                       // Available: MSX2 (Do Not Call SUB-ROM While Screen Modes 4..8 Are Changed)

constant NSETRD($016E) //  Function: Enable VRAM To Be Read By Setting Address
                       //     Input: HL = VRAM Address
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

constant NSTWRT($0171) //  Function: Enable VRAM To Be Written By Setting Address 
                       //     Input: HL = VRAM Address
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

constant NRDVRM($0174) //  Function: Read Data From VRAM (16-Bit Address: $0000..$FFFF)
                       //     Input: HL = VRAM Address
                       //    Output: A = Value Which Was Read
                       // Registers: F
                       // Available: MSX2

constant NWRVRM($0177) //  Function: Write Data To VRAM (16-Bit Address: $0000..$FFFF)
                       //     Input: HL = VRAM Address, A = Data To Write
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

//============================
// Entries Appended For MSX2+
//============================
constant RDBTST($017A) //  Function: Read Value Of I/O Port $F4
                       //     Input: NONE
                       //    Output: A = Value Read
                       // Registers: AF
                       // Available: MSX2+

constant WRBTST($017D) //  Function: Write Value To I/O Port $F4
                       //     Input: A = Value To Write (Bit 7 = Show MSX2+ Startup Screen(0), Skipped(1))
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX2+

//==================================
// Entries Appended For MSX Turbo-R
//==================================
constant CHGCPU($0180) //  Function: Change CPU Mode
                       //     Input: A = Settings: %L00000MM - L = LED (Indicates IF Turbo LED Is Switched With CPU Mode)
                       //            M = CPU Mode - 0 = Z80 ROM Mode, 1 = R800 ROM Mode, 2 = R800 DRAM Mode
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX Turbo-R

constant GETCPU($0183) //  Function: Returns Current CPU Mode
                       //     Input: NONE
                       //    Output: A = Settings: %L00000MM - L = LED (Indicates IF Turbo LED Is Switched With CPU Mode
                       //            M = CPU Mode - 0 = Z80 ROM Mode, 1 = R800 ROM Mode, 2 = R800 DRAM Mode
                       // Registers: AF
                       // Available: MSX Turbo-R

constant PCMPLY($0186) //  Function: Play Specified Memory Area Through PCM Chip
                       //     Input:  A = Settings: %V00000QQ - V = VRAM Usage Flag, Q = Quality Parameter (Speed: 0 = Fast)
                       //            HL = Start Address In RAM Or VRAM
                       //            BC = Length Of Area To Play
                       //             D = Bit 0 Becomes Bit 17 Of Area Length When Using VRAM
                       //             E = Bit 0 Becomes Bit 17 Of Start Address When Using VRAM
                       //    Output: CY-Flag Set IF Aborted With CTRL-STOP
                       // Registers: ALL
                       // Available: MSX Turbo-R

constant PCMREC($0189) //  Function: Record Audio Using PCM Chip To Specified Memory Area
                       //     Input:  A = Settings: %VTTTTCQQ - V = VRAM Usage Flag, T = Treshold,
                       //             C = Zero-Data Compression, Q = Quality Parameter (Speed: 0 = Fast)
                       //            HL = Start Address In RAM Or VRAM
                       //            BC = Length Of Area To Record
                       //             D = Bit 0 Becomes Bit 17 Of Area Length When Using VRAM
                       //             E = Bit 0 Becomes Bit 17 Of Start Address When Using VRAM
                       //    Output: CY-Flag Set IF Aborted With CTRL-STOP
                       // Registers: ALL
                       // Available: MSX Turbo-R

//=========
// SUB-ROM
//=========

//================
// BASIC Routines
//================
constant  PAINT($0069) //  Function: Paint Graphic-Screen
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant   PSET($006D) //  Function: Set Point
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant ATRSCN($0071) //  Function: Scans Color Attribute
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant  GLINE($0075) //  Function: Draw Line
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant DOBOXF($0079) //  Function: Draw Filled Box
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant DOLINE($007D) //  Function: Draw Line
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant BOXLIN($0081) //  Function: Draw Box
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

//====================
// NON-BASIC Routines
//====================
constant DOGRPH($0085) //  Function: Draw Line
                       //     Input: Start Point: BC = X-Coordinate, HL = Y-Coordinate
                       //              End Point:  GXPOS ($FCB3) = X-Coordinate, GYPOS ($FCB5) = Y-Coordinate
                       //                  Color: ATRBYT ($F3F3) = Attribute
                       // Logical Operation Code: LOGOPR ($FB02) = Code
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

constant  GRPRT($0089) //  Function: Display A Character On The Graphic-Screen (Active In Screen Modes 5..8)
                       //     Input:   Character: A = Character Code To Be Displayed
                       //                  Color: ATRBYT ($F3F3) = Attribute
                       // Logical Operation Code: LOGOPR ($FB02) = Code
                       //    Output: NONE
                       // Registers: NONE
                       // Available: MSX2

constant SCALXYB($008D) //  Function: Clip X,Y Coordinates (Against Screen Border) (Same As SCALXY In MAIN-ROM)
                        //     Input: BC = X-Coordinate, DE = Y-Coordinate
                        //    Output: BC = Clipped X-Coordinate, DE = Clipped Y-Coordinate
                        // Registers: AF
                        // Available: MSX2

constant MAPXYC($0091) //  Function: Convert X,Y Coordinates Position To Address: & Mask In CLOC & CMASK
                       //     Input: BC = X-Coordinate, DE = Y-Coordinate
                       //    Output: HL = VRAM Address: In SCREEN 3 (Also In CLOC)
                       //             A = Mask:         In SCREEN 3 (Also In CMASK)
                       //            HL = X-Coordinate: In SCREEN 5..8 (Also In CLOC)
                       //             A = Y-Coordinate: In SCREEN 5..8 (Also In CMASK)
                       // Registers: F
                       // Available: MSX2

constant  READCB($0095) //  Function: Read Attribute Byte Of Current Screen Pixel (Same As READC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: A = Pixel Attribute
                        // Registers: AF
                        // Available: MSX2

constant SETATRB($0099) //  Function: Set Attribute Byte In ATRBYT ($F3F2) (Same As SETATR In MAIN-ROM)
                        //     Input: A = Attribute
                        //    Output: CY-Flag Set IF Wrong Attribute
                        // Registers: F
                        // Available: MSX2

constant   SETCB($009D) //  Function: Set Attribute Of Pixel (Same As SETC In MAIN-ROM)
                        //     Input:   CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //            ATRBYT = Attribute Byte
                        //    Output: NONE
                        // Registers: AF
                        // Available: MSX2

constant TRIGHT($00A1) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute RIGHTC (Move Pixel Right)
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       //              CY-Flag Set IF Operation Would End Outside Screen Border
                       // Registers: AF
                       // Available: MSX2 (SCREEN 3 Only)

constant RIGHTCB($00A5) //  Function: Move Pixel Right (Same As RIGHTC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant TLEFTC($00A9) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute LEFTC (Move Pixel Left)
                       //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                       //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                       //              CY-Flag Set IF Operation Would End Outside Screen Border
                       // Registers: AF
                       // Available: MSX2 (SCREEN 3 Only)

constant  LEFTCB($00AD) //  Function: Move Pixel Left (Same As LEFTC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant TDOWNCB($00B1) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute DOWNC (Move Pixel Down) (Same As TDOWNC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        //              CY-Flag Set IF Operation Would End Outside Screen Border
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant  DOWNCB($00B5) //  Function: Move Pixel Down (Same As DOWNC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant   TUPCB($00B9) //  Function: Test Against Screen Border, IF Inside Screen Border, Execute UPC (Move Pixel Up) (Same As TUPC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        //              CY-Flag Set IF Operation Would End Outside Screen Border
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant    UPCB($00BD) //  Function: Move Pixel Up (Same As UPC In MAIN-ROM)
                        //     Input: CLOC = X-Coordinate, CMASK = Y-Coordinate
                        //    Output: CLOC = New X-Coordinate, CMASK = New Y-Coordinate
                        // Registers: AF
                        // Available: MSX2 (SCREEN 3 Only)

constant  SCANRB($00C1) //  Function: Scan Screen Pixels Right (Same As SCANR In MAIN-ROM)
                        //     Input: B = "Suspend" Flag, C = Border-Counting
                        //    Output: C = "Pixel-Changed" Flag, DE = Border-Counting
                        // Registers: ALL
                        // Available: MSX2

constant  SCANLB($00C5) //  Function: Scan Screen Pixels Left (Same As SCANL In MAIN-ROM)
                        //     Input: B = "Suspend" Flag, C = Border-Counting
                        //    Output: C = "Pixel-Changed" Flag, DE = Border-Counting
                        // Registers: ALL
                        // Available: MSX2

constant NVBXLN($00C9) //  Function: Draw A Box
                       //     Input: Start Point: BC = X-Coordinate, DE = Y-Coordinate
                       //              End Point:  GXPOS ($FCB3) = X-Coordinate, GYPOS ($FCB5) = Y-Coordinate
                       //                  Color: ATRBYT ($F3F3) = Attribute
                       // Logical Operation Code: LOGOPR ($FB02) = Code
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant NVBXFL($00CD) //  Function: Draw Filled Box
                       //     Input: Start Point: BC = X-Coordinate, DE = Y-Coordinate
                       //              End Point:  GXPOS ($FCB3) = X-Coordinate, GYPOS ($FCB5) = Y-Coordinate
                       //                  Color: ATRBYT ($F3F3) = Attribute
                       // Logical Operation Code: LOGOPR ($FB02) = Code
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant CHGMODB($00D1) //  Function: Change Screen Mode (Same As CHGMOD In MAIN-ROM)
                        //     Input: A = Screen Mode (0..8)
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant INITXTB($00D5) //  Function: Initialise Screen To TEXT1 Mode (40x24) (Same As INITXT In MAIN-ROM)
                        //     Input: TXTNAM ($F3B3) = Pattern Name Table
                        //            TXTCGP ($F3B7) = Pattern Generator Table
                        //            LINL40 ($F3AE) = Length Of Line
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant INIT32B($00D9) //  Function: Initialise Screen To GRAPHIC1 Mode (32x24) (Same As INIT32 In MAIN-ROM)
                        //     Input: T32NAM ($F3BD) = Pattern Name Table
                        //            T32COL ($F3BF) = Color Table
                        //            T32CGP ($F3C1) = Pattern Generator Table
                        //            T32ATR ($F3C3) = Sprite Attribute Table
                        //            T32PAT ($F3C5) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant INIGRPB($00DD) //  Function: Initialise Screen To High-Resolution Graphics Mode (Same As INIGRP In MAIN-ROM)
                        //     Input: GRPNAM ($F3C7) = Pattern Name Table
                        //            GRPCOL ($F3C9) = Color Table
                        //            GRPCGP ($F3CB) = Pattern Generator Table
                        //            GRPATR ($F3CD) = Sprite Attribute Table
                        //            GRPPAT ($F3CF) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant INIMLTB($00E1) //  Function: Initialise Screen To MULTI COLOR Mode (Same As INIMLT In MAIN-ROM)
                        //     Input: MLTNAM ($F3D1) = Pattern Name Table
                        //            MLTCOL ($F3D3) = Color Table
                        //            MLTCGP ($F3D5) = Pattern Generator Table
                        //            MLTATR ($F3D7) = Sprite Attribute Table
                        //            MLTPAT ($F3D9) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant SETTXTB($00E5) //  Function: Set VDP To Text Mode (40x24) (Same As SETTXT In MAIN-ROM)
                        //     Input: TXTNAM ($F3B3) = Pattern Name Table
                        //            TXTCGP ($F3B7) = Pattern Generator Table
                        //            LINL40 ($F3AE) = Length Of Line
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant SETT32B($00E9) //  Function: Set VDP To Text Mode (32x24) (Same As SETT32 In MAIN-ROM)
                        //     Input: T32NAM ($F3BD) = Pattern Name Table
                        //            T32COL ($F3BF) = Color Table
                        //            T32CGP ($F3C1) = Pattern Generator Table
                        //            T32ATR ($F3C3) = Sprite Attribute Table
                        //            T32PAT ($F3C5) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant SETGRPB($00ED) //  Function: Set VDP To High-Resolution Mode (Same As SETGRP In MAIN-ROM)
                        //     Input: GRPNAM ($F3C7) = Pattern Name Table
                        //            GRPCOL ($F3C9) = Color Table
                        //            GRPCGP ($F3CB) = Pattern Generator Table
                        //            GRPATR ($F3CD) = Sprite Attribute Table
                        //            GRPPAT ($F3CF) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant SETMLTB($00F1) //  Function: Set VDP To MULTI COLOR Mode (Same As SETMLT In MAIN-ROM)
                        //     Input: MLTNAM ($F3D1) = Pattern Name Table
                        //            MLTCOL ($F3D3) = Color Table
                        //            MLTCGP ($F3D5) = Pattern Generator Table
                        //            MLTATR ($F3D7) = Sprite Attribute Table
                        //            MLTPAT ($F3D9) = Sprite Generator Table
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant CLRSPRB($00F5) //  Function: Initialise All Sprites (Same As CLRSPR In MAIN-ROM)
                        //            Sprite Pattern Cleared To Zero, Sprite Number To Sprite Plane Number
                        //            Sprite Color To Foreground Color
                        //            Sprite Vertical Location Set To 209 (Mode 0..3) Or 217 (Mode 4..8)
                        //     Input: SCRMOD ($FCAF) = Screen Mode
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant CALPATB($00F9) //  Function: Return Address Of Sprite Generator Table (Same As CALPAT In MAIN-ROM)
                        //     Input:  A = Sprite Number
                        //    Output: HL = Returned Address
                        // Registers: AF, DE, HL
                        // Available: MSX2

constant CALATRB($00FD) //  Function: Return Address Of Sprite Attribute Table (Same As CALATR In MAIN-ROM)
                        //     Input:  A = Sprite Number
                        //    Output: HL = Returned Address
                        // Registers: AF, DE, HL
                        // Available: MSX2

constant GSPSIZB($0101) //  Function: Return Current Sprite Size (Same As GSPSIZ In MAIN-ROM)
                        //     Input: NONE
                        //    Output: A = Sprite Size (In Bytes)
                        //            CY-Flag Set IF (Size == 16x16), ELSE CY-Flag Reset
                        // Registers: AF
                        // Available: MSX2

//========================
// MSX2 Specific Routines
//========================
constant GETPAT($0105) //  Function: Return Current Character Pattern
                       //     Input: A = Character Code
                       //    Output: PATWRK ($FC40 Onwards) = Character Pattern
                       // Registers: ALL
                       // Available: MSX2 (Same As Non-Callable Routine In MSX1-BIOS)

constant WRTVRMB($0109) //  Function: Write Data To VRAM (16-Bit Address: $0000..$FFFF) (Same As NWRVRM In MAIN-ROM)
                        //     Input: HL = VRAM Address, A = Data To Write
                        //    Output: NONE
                        // Registers: AF
                        // Available: MSX2

constant  RDVRMB($010D) //  Function: Read Data From VRAM (16-Bit Address: $0000..$FFFF) (Same As NRDVRM In MAIN-ROM)
                        //     Input: HL = VRAM Address
                        //    Output: A = Data Which Was Read
                        // Registers: AF
                        // Available: MSX2

constant CHGCLRB($0111) //  Function: Change Screen Color (Same As CHGCLR In MAIN-ROM)
                        //     Input: A = Screen Mode
                        //            FORCLR ($F3E9) = Foreground Color
                        //            BAKCLR ($F3EA) = Background Color
                        //            BDRCLR ($F3EB) = Border Color
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant CLSSUB($0115) //  Function: Clear Screen
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant CLRTXT($0119) //  Function: Clear Text-Screen
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant DSPFNKB($011D) //  Function: Display Function Keys (Same As DSPFNK In MAIN-ROM)
                        //     Input: NONE
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant  DELLNO($0121) //  Function: Remove Line In Text-Screen
                        //     Input: L = Line Number
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant  INSLNO($0125) //  Function: Add Line To Text-Screen
                        //     Input: L = Line Number
                        //    Output: NONE
                        // Registers: ALL
                        // Available: MSX2

constant  PUTVRM($0129) //  Function: Put Character On Text-Screen
                        //     Input: L = X-Position, H = Y-Position
                        //    Output: NONE
                        // Registers: AF
                        // Available: MSX2

constant WRTVDPB($012D) //  Function: Write Data To VDP Register (Same As WRTVDP In MAIN-ROM)
                        //     Input: C = VDP Register Number (0..23, 32..46), B = Data To Write
                        //    Output: NONE
                        // Registers: AF, BC
                        // Available: MSX2

constant VDPSTA($0131) //  Function: Read Data From VDP Register
                       //     Input: A = Register Number (0..9)
                       //    Output: A = Data That Has Been Read
                       // Registers: F
                       // Available: MSX2

constant KYKLOK($0135) //  Function: Control KANA-Key & KANA-Lamp (Japan)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

constant PUTCHR($0139) //  Function: Get Key-Code From Keyboard, Convert To KANA & Place In Buffer (Japan)
                       //     Input: Z-Flag = Conversion Mode (Set IF Not In Conversion Mode)
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

constant SETPAG($013D) //  Function: Switche Page
                       //     Input: DPPAGE ($FAF5) = Display Page Number
                       //            ACPAGE ($FAF6) =  Active Page Number
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

//==================
// Palette Routines
//==================
constant INIPLT($0141) //  Function: Initialise Palette (Current Palette Is Saved To VRAM)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: AF, BC, DE
                       // Available: MSX2

constant RSTPLT($0145) //  Function: Restore Palette From VRAM
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: AF, BC, DE
                       // Available: MSX2

constant GETPLT($0149) //  Function: Get Colour Code From Palette
                       //     Input: D = Palette Number (0..15)
                       //    Output: B = Red & Blue: %RRRRBBBB - R = Red Code, B = Blue Code
                       //            C = Green: %0000GGGG - G = Green Code
                       // Registers: AF, DE
                       // Available: MSX2

constant SETPLT($014D) //  Function: Set Colour Code To Palette
                       //     Input: D = Palette Number (0..15)
                       //            A = Red & Blue: %RRRRBBBB - R = Red Code, B = Blue Code
                       //            E = Green: %0000GGGG - G = Green Code
                       //    Output: NONE
                       // Registers: AF
                       // Available: MSX2

//================
// BASIC Routines
//================
constant PUTSPRT($0151) //  Function: Set Sprites
                        //     Input: HL = BASIC Text-Pointer
                        //    Output: HL = Adapted BASIC Text-Pointer
                        // Registers: ALL
                        // Available: MSX2 (BASIC!)

constant  COLOR($0155) //  Function: Change Screen, Sprite, Or Palette Color Value
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant SCREEN($0159) //  Function: Change Screen Mode
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant WIDTHS($015D) //  Function: Change Text-Screen Width
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant    VDP($0161) //  Function: Write Data To VDP Register
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant   VDPF($0165) //  Function: Read Data From VDP Register
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant   BASE($0169) //  Function: Write VDP Base Register
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant  BASEF($016D) //  Function: Read VDP Base Register
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant  VPOKE($0171) //  Function: Write Byte To VRAM
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant  VPEEK($0175) //  Function: Read Byte From VRAM
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant   SETS($0179) //  Function: Set BEEP, ADJUST, TIME & DATE
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

//====================
// NON-BASIC Routines
//====================
constant  BEEPB($017D) //  Function: Generate BEEP (Same As BEEP In MAIN-ROM)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant PROMPT($0181) //  Function: Display Prompt (Default: “Ok”)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant SDFSCR($0185) //  Function: Recover Screen-Parameter Of Clock-Chip
                       //  When CY-Flag Set, Function-Key Text Will Display
                       //     Input: CY-Flag Reset After MSX-DOS Call
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant SETSCR($0189) //  Function: Recover Screen-Parameter Of Clock-Chip, & Print Welcome Message
                       //  When CY-Flag Set, Function-Key Text Will Display
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  SCOPY($018D) //  Function: Copy VRAM, Array & DISK-FILE
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

//===================
// BIT-BLIT Routines
//===================
// Mostly Executed by the VDP, Parameters Must Be Passed Through System RAM ($F562)
// See MSX2 System Variables For More Detail, HL Must Be $F562 When Calling
constant  BLTVV($0191) //  Function: Copy VRAM To VRAM
                       //     Input: SX, SY, DX, DY, NX, NY, ARG, L_OP
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  BLTVM($0195) //  Function: Copy MAIN-RAM To VRAM
                       //     Input: SX = Address Of Screen Data In RAM, DX, DY, ARG, L_OP,
                       //            NX & NY Must Be In Screen Data
                       //    Output: CY-Flag Set IF Data Failure In RAM
                       // Registers: ALL
                       // Available: MSX2

constant  BLTMV($0199) //  Function: Copy VRAM To MAIN-RAM
                       //     Input: DX = Address Of Screen Data In RAM, SX, SY, ARG, L_OP,
                       //            NX & NY Must Be In Screen Data
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  BLTVD($019D) //  Function: Copy DISK-FILE To VRAM
                       //     Input: SX = Address Of Disk Filename, DX, DY, ARG, L_OP,
                       //            NX & NY Must Be In Screen Data
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  BLTDV($01A1) //  Function: Copy VRAM To DISK-FILE
                       //     Input: DX = Address Of Disk Filename, SX, SY, NX, NY, ARG
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  BLTMD($01A5) //  Function: Copy DISK-FILE To MAIN-RAM
                       //     Input: SX = Address Of Disk Filename
                       //            DX = Start Address In RAM
                       //            DY = End Address In RAM
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant  BLTDM($01A9) //  Function: Copy MAIN-RAM To DISK-FILE
                       //     Input: DX = Address Of Disk Filename
                       //            SX = Start Address In RAM
                       //            SY = End Address In RAM
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

//===============
// Miscellaneous
//===============
constant NEWPAD($01AD) //  Function: Read Status Of Mouse Or Light-Pen
                       //     Input: Call Setting Following Data In A:
                       //            Descriptions In Parenthesis Are Return Values
                       //  8 ....... Light-Pen Check ($FF = Available / Touching Screen)
                       //  9 ....... Read X-Coordinate
                       // 10 ....... Read Y-Coordinate
                       // 11 ....... Read Light-Pen Switch Status ($FF = Pressed)
                       // 12 ....... Whether Mouse Is Connected To Port 1 ($FF = Available)
                       // 13 ....... Read Offset In X-Direction
                       // 14 ....... Read Offset In Y-Direction
                       // 15 ....... No Function (Always 0)
                       // 16 ....... Whether Mouse Is Connected To Port 2 ($FF = Available)
                       // 17 ....... Read Offset In X-Direction
                       // 18 ....... Read Offset In Y-Direction
                       // 19 ....... No Function (Always 0)
                       // 21 ....... 2nd Light-Pen Check ($FF = Available / Touching Screen)
                       // 22 ....... Read X-Coordinate
                       // 23 ....... Read Y-Coordinate
                       // 24 ....... Read 2nd Light-Pen Switch Status ($FF = Pressed)
                       //    Output: A
                       // Registers: ALL
                       // Available: MSX2 (Access Via GTPAD In MAIN-ROM, Numbers 8 & Up Will Be Forwarded To This Call)

constant GETPUT($01B1) //  Function: GET TIME, GET DATE & PUT KANJI
                       //     Input: HL = BASIC Text-Pointer
                       //    Output: HL = Adapted BASIC Text-Pointer
                       // Registers: ALL
                       // Available: MSX2 (BASIC!)

constant CHGMDP($01B5) //  Function: Change Screen Mode, Palette Is Initialised
                       //     Input: A = Screen Mode (0..8)
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant   REVI($01B9) //  Function: Not Used (Reserved Entry)
                       //     Input: NONE
                       //    Output: NONE
                       // Registers: ALL
                       // Available: MSX2

constant KNJPRT($01BD) //  Function: Send A Kanji Character To The Graphic-Screen (Mode 5..8)
                       //     Input: BC = JIS Kanji-Character Code, A = Display Mode
                       //            The Display Mode Is Similar To PUT KANJI BASIC Command:
                       // 0 ........ Display In 16x16 Dots (FULL)
		       // 1 ........ Display Even Dots (EVEN)
		       // 2 ........ Display Odd Dots (ODD)
                       //
                       // Available: MSX2

constant REDCLK($01F5) //  Function: Read CLOCK-RAM Data
                       //     Input: C = CLOCK-RAM Address: %00BBAAAA - A = Address (0..15), B = Block Number (0..3)
                       //    Output: A = Data Which Was Read (Lower 4-Bits)
                       // Registers: F
                       // Available: MSX2

constant WRTCLK($01F9) //  Function: Write CLOCK-RAM Data
                       //     Input: C = CLOCK-RAM Address: %00BBAAAA - A = Address (0..15), B = Block Number (0..3)
                       //            A = Data To Write
                       //    Output: NONE
                       // Registers: F
                       // Available: MSX2