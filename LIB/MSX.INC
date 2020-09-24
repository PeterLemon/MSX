//=============(Key: R=Read, W=Write)
// MSX Include
//=============

//======================
// MSX System Variables
//======================

//=========================================
// MSX System Variables Located In SUB-ROM
//=========================================
constant  SUBID($0000) //  SUBID - String "CD", Identification Of MSX SUB-ROM                2B/R
constant STRTUP($0000) // STRTUP - Execution Address For Startup Screen On MSX2 Upwards      2B/R

//==========================================
// MSX System Variables Located In MAIN-ROM
//==========================================
constant CGTABL($0004) // CGTABL - Base Address Of MSX Character Set In ROM                  2B/R
constant  VDPDR($0006) //  VDPDR - Base Port Address For VDP Data Read                       1B/R
constant  VDPDW($0007) //  VDPDW - Base Port Address For VDP Data Write                      1B/R

constant SYSVER($002B) // SYSVER - BASIC System Version: %FDDDCCCC                           1B/R
                       // C = Character Set: 0 = Japanese, 1 = International, 2 = Korean
                       // D = Date Format: 0 = Y-M-D, 1 = M-D-Y, 2 = D-M-Y
                       // F = Default Interrupt Frequency: 0 = 60Hz, 1 = 50Hz

constant ROMVER($002C) // ROMVER - BASIC ROM Version: %BBBBKKKK                              1B/R
                       // K = Keyboard Type: 0 = Japanese, 1 = International (QWERTY),
                       //                    2 = French (AZERTY), 3 = UK, 4 = German (DIN)
                       // B = BASIC Version: 0 = Japanese, 1 = International

constant MSXVER($002D) // MSXVER - MSX Version: %VVVVVVVV                                    1B/R
                       // V = MSX Version: 0 = MSX, 1 = MSX2, 2 = MSX2+, 3 = MSX Turbo-R

constant INMIDI($002D) // INMIDI - Internal MSX-MIDI: %0000000M                              1B/R
                       // M = Internal MSX-MIDI: 0 = Missing, 1 = Present (MSX Turbo-R Only)

//===================================================
// MSX-DOS (DiskROM) System Variables Located In RAM
//===================================================
// Only Initialized When DiskROM Is Present (When Diskdrive Or Harddisk Interface Connected)
constant RAMAD0($F341) // RAMAD0 - Slot Address Of RAM In Page 0 (DOS)                       1B/RW
constant RAMAD1($F342) // RAMAD1 - Slot Address Of RAM In Page 1 (DOS)                       1B/RW
constant RAMAD2($F343) // RAMAD2 - Slot Address Of RAM In Page 2 (DOS/BASIC)                 1B/RW
constant RAMAD3($F344) // RAMAD3 - Slot Address Of RAM In Page 3 (DOS/BASIC)                 1B/RW
constant DROMAD($F348) // DROMAD - Slot Main DiskROM Slot Address                            1B/RW

//=====================================
// MSX System Variables Located In RAM
//=====================================
// Start Of MSX BIOS System Area
constant RDPRIM($F380) // RDPRIM - Routine That Reads From A Primary Slot                    5B/RW
constant WRPRIM($F385) // WRPRIM - Routine That Writes To A Primary Slot                     7B/RW
constant CLPRIM($F38C) // CLPRIM - Routine That Calls A Routine In A Primary Slot           14B/RW

constant USRTAB($F39A) // USRTAB - Address Table To Call With BASIC USR0..USR9:             20B/RW
constant USR0AD($F39A) // USR0AD - Address To Call With BASIC USR0                           2B/RW
constant USR1AD($F39C) // USR1AD - Address To Call With BASIC USR1                           2B/RW
constant USR2AD($F39E) // USR2AD - Address To Call With BASIC USR2                           2B/RW
constant USR3AD($F3A0) // USR3AD - Address To Call With BASIC USR3                           2B/RW
constant USR4AD($F3A2) // USR4AD - Address To Call With BASIC USR4                           2B/RW
constant USR5AD($F3A4) // USR5AD - Address To Call With BASIC USR5                           2B/RW
constant USR6AD($F3A6) // USR6AD - Address To Call With BASIC USR6                           2B/RW
constant USR7AD($F3A8) // USR7AD - Address To Call With BASIC USR7                           2B/RW
constant USR8AD($F3AA) // USR8AD - Address To Call With BASIC USR8                           2B/RW
constant USR9AD($F3AC) // USR9AD - Address To Call With BASIC USR9                           2B/RW

constant LINL40($F3AE) // LINL40 - Width For SCREEN 0 (Default = 37)                         1B/RW
constant LINL32($F3AF) // LINL32 - Width For SCREEN 1 (Default = 29)                         1B/RW
constant LINLEN($F3B0) // LINLEN - Width For Current Text Mode                               1B/RW
constant CRTCNT($F3B1) // CRTCNT - Number Of Lines On Screen                                 1B/RW
constant CLMLST($F3B2) // CLMLST - Column Space On Screen                                    1B/RW
constant TXTNAM($F3B3) // TXTNAM - BASE(0) - TEXT SCREEN 0 Name Table                        2B/RW
constant TXTCOL($F3B5) // TXTCOL - BASE(1) - TEXT SCREEN 0 Color Table                       2B/RW
constant TXTCGP($F3B7) // TXTCGP - BASE(2) - TEXT SCREEN 0 Character Pattern Table           2B/RW
constant TXTATR($F3B9) // TXTATR - BASE(3) - TEXT SCREEN 0 Sprite Attribute Table            2B/RW
constant TXTPAT($F3BB) // TXTPAT - BASE(4) - TEXT SCREEN 0 Sprite Pattern Table              2B/RW
constant T32NAM($F3BD) // T32NAM - BASE(5) - TEXT SCREEN 1 Name Table                        2B/RW
constant T32COL($F3BF) // T32COL - BASE(6) - TEXT SCREEN 1 Color Table                       2B/RW
constant T32CGP($F3C1) // T32CGP - BASE(7) - TEXT SCREEN 1 Character Pattern Table           2B/RW
constant T32ATR($F3C3) // T32ATR - BASE(8) - TEXT SCREEN 1 Sprite Attribute Table            2B/RW
constant T32PAT($F3C5) // T32PAT - BASE(9) - TEXT SCREEN 1 Sprite Pattern Table              2B/RW
constant GRPNAM($F3C7) // GRPNAM - BASE(10) - GRAPHICS SCREEN 2 Name Table                   2B/RW
constant GRPCOL($F3C9) // GRPCOL - BASE(11) - GRAPHICS SCREEN 2 Color Table                  2B/RW
constant GRPCGP($F3CB) // GRPCGP - BASE(12) - GRAPHICS SCREEN 2 Character Pattern Table      2B/RW
constant GRPATR($F3CD) // GRPATR - BASE(13) - GRAPHICS SCREEN 2 Sprite Attribute Table       2B/RW
constant GRPPAT($F3CF) // GRPPAT - BASE(14) - GRAPHICS SCREEN 2 Sprite Pattern Table         2B/RW
constant MLTNAM($F3D1) // MLTNAM - BASE(15) - MULTI COLOR SCREEN 3 Name Table                2B/RW
constant MLTCOL($F3D3) // MLTCOL - BASE(16) - MULTI COLOR SCREEN 3 Color Table               2B/RW
constant MLTCGP($F3D5) // MLTCGP - BASE(17) - MULTI COLOR SCREEN 3 Character Pattern Table   2B/RW
constant MLTATR($F3D7) // MLTATR - BASE(18) - MULTI COLOR SCREEN 3 Sprite Attribute Table    2B/RW
constant MLTPAT($F3D9) // MLTPAT - BASE(19) - MULTI COLOR SCREEN 3 Sprite Pattern Table      2B/RW

constant CLIKSW($F3DB) // CLIKSW - Key Press Click Switch (SCREEN n Writes To This Address)  1B/RW
                       // 0 = When Key Press Click Disabled
                       // 1 = When Key Press Click Enabled

constant   CSRY($F3DC) //   CSRY - Current Cursor Y-Position (Row)                           1B/RW
constant   CSRX($F3DD) //   CSRX - Current Cursor X-Position (Column)                        1B/RW

constant CNSDFG($F3DE) // CNSDFG - Function Keys Display                                     1B/RW
                       // 0 = When Function Keys Display Disabled
                       // 1 = When Function Keys Display Enabled

constant RG0SAV($F3DF) // RG0SAV - Mirror Of VDP Register 0 (BASIC: VDP(0))                  1B/RW
constant RG1SAV($F3E0) // RG1SAV - Mirror Of VDP Register 1 (BASIC: VDP(1))                  1B/RW
constant RG2SAV($F3E1) // RG2SAV - Mirror Of VDP Register 2 (BASIC: VDP(2))                  1B/RW
constant RG3SAV($F3E2) // RG3SAV - Mirror Of VDP Register 3 (BASIC: VDP(3))                  1B/RW
constant RG4SAV($F3E3) // RG4SAV - Mirror Of VDP Register 4 (BASIC: VDP(4))                  1B/RW
constant RG5SAV($F3E4) // RG5SAV - Mirror Of VDP Register 5 (BASIC: VDP(5))                  1B/RW
constant RG6SAV($F3E5) // RG6SAV - Mirror Of VDP Register 6 (BASIC: VDP(6))                  1B/RW
constant RG7SAV($F3E6) // RG7SAV - Mirror Of VDP Register 7 (BASIC: VDP(7))                  1B/RW
constant STATFL($F3E7) // STATFL - Mirror Of VDP Status Flags Register (BASIC: VDP(8))       1B/RW

constant TRGFLG($F3E8) // TRGFLG - Trigger Buttons & Space-Bar State Flags: %BA21000S        1B/RW
                       // S =   Space-Bar, Trigger 0: 0 = Pressed, 1 = Released
                       // 1 = Joy-Stick 1, Trigger 1: 0 = Pressed, 1 = Released
                       // 2 = Joy-Stick 1, Trigger 2: 0 = Pressed, 1 = Released
                       // A = Joy-Stick 2, Trigger 1: 0 = Pressed, 1 = Released
                       // B = Joy-Stick 2, Trigger 2: 0 = Pressed, 1 = Released

constant FORCLR($F3E9) // FORCLR - Foreground Color                                          1B/RW
constant BAKCLR($F3EA) // BAKCLR - Background Color                                          1B/RW
constant BDRCLR($F3EB) // BDRCLR - Border Color                                              1B/RW

constant MAXUPD($F3EC) // MAXUPD - Jump Instruction Used By BASIC LINE Command               3B/RW
                       // Used In These Routines: RIGHTC, LEFTC, UPC & DOWNC

constant MINUPD($F3EF) // MINUPD - Jump Instruction Used By BASIC LINE Command               3B/RW
                       // Used In These Routines: RIGHTC, LEFTC, UPC & DOWNC

constant ATRBYT($F3F2) // ATRBYT - Attribute Byte (Graphical Routines Read Color)            1B/RW
constant QUEUES($F3F3) // QUEUES - Queue Table Address (QUETAB Initial Value)                2B/RW
constant FRCNEW($F3F5) // FRCNEW - CLOAD Flag: 0 = When CLOAD, 255 = When NOT CLOAD          1B/RW
constant SCNCNT($F3F6) // SCNCNT - Key Scan Counter: 0 = Ready To Scan Pressed Keys          1B/RW
constant REPCNT($F3F7) // REPCNT - Key Repeat Delay Counter: 0 = Key Will Repeat             1B/RW
constant PUTPNT($F3F8) // PUTPNT - Keyboard Buffer Address To Write Character                2B/RW
constant GETPNT($F3FA) // GETPNT - Keyboard Buffer Address To Read Character                 2B/RW
constant  CS120($F3FC) //  CS120 - Cassette I/O Parameters For 1200 Baud                     5B/RW
constant  CS240($F401) //  CS240 - Cassette I/O Parameters For 2400 Baud                     5B/RW
constant    LOW($F406) //    LOW - Signal Delay When Writing 0 To Tape                       2B/RW
constant   HIGH($F408) //   HIGH - Signal Delay When Writing 1 To Tape                       2B/RW
constant HEADER($F40A) // HEADER - Delay Of Tape Header Sync Block                           1B/RW
constant ASPCT1($F40B) // ASPCT1 - Horizontal / Vertical Aspect Ratio For CIRCLE Command     2B/RW
constant ASPCT2($F40D) // ASPCT2 - Horizontal / Vertical Aspect Ratio For CIRCLE Command     2B/RW
constant ENDPRG($F40F) // ENDPRG - Pointer For RESUME NEXT Command                           5B/RW
constant ERRFLG($F414) // ERRFLG - BASIC Error Flag Code                                     1B/RW

constant LPTPOS($F415) // LPTPOS - Printer Head Position:                                    1B/RW
                       // Read By BASIC Function LPOS & Used By LPRINT BASIC Command

constant PRTFLG($F416) // PRTFLG - Printer Output Flag Read By OUTDO:                        1B/RW
                       // 0 = Print To Screen, 1 = Print To Printer

constant NTMSXP($F417) // NTMSXP - Printer Type Read By OUTDO, SCREEN n Writes To Address:   1B/RW
                       // 0 = MSX Printer, 1 = Non-MSX Printer

constant RAWPRT($F418) // RAWPRT - Raw Printer Output Read By OUTDO:                         1B/RW
                       // 0 = Set Tab & Unknown Character To Space & Remove Graphics Headers
                       // 1 = Send Data Just Like It Gets It (RAW Data)

constant VLZADR($F419) // VLZADR - Address Of Data Replaced By ‘O’ In BASIC Function VAL("") 2B/RW
constant VLZDAT($F41B) // VLZDAT - Original Value From Address Pointed To With VLZADR        1B/RW

constant CURLIN($F41C) // CURLIN - Current Line Number BASIC Interpreter Is Working On       1B/RW
                       // In Direct Mode It Will Be Filled With #FFFF

constant CHRSID($F91F) // CURLIN - Character Set SlotID                                      1B/RW
constant CHRSAD($F920) // CURLIN - Character Set Address                                     2B/RW

constant QUETAB($F959) // QUETAB - Queue-Table Containing Queue Information For 4 Queues    24B/RW
                       // 3 PLAY Queues & 1 RS232 Queue, Using 6-Byte Information Blocks:
                       // Byte 0 = Queue Head Offset (For Writing)
                       // Byte 1 = Queue Tail Offset (For Reading)
                       // Byte 2 = Flag Indicating Whether A Byte Has Been Returned
                       // Byte 3 = Queue Size
                       // Byte 4 & 5 = Queue Start Address

constant EXBRSA($FAF8) // EXBRSA - SUBROM Slot Address (EXTENDED BIOS-ROM Slot Address)      1B/RW
constant  XSAVE($FAFE) //  XSAVE - Light Pen X Coordinate Read From Device (Internal Use)    1B/RW

constant  XOFFS($FAFF) //  XOFFS - Light Pen X Calibration Offset & Interrupt %IXXXXXXX:     1B/RW
                       // X = X Calibration Offset (7-Bit)
                       // I = Light Pen Interrupt (Used Internally By MSX-BIOS, Do Not Set)

constant  YSAVE($FB00) //  YSAVE - Light Pen Y Coordinate Read From Device (Internal Use)    1B/RW

constant  YOFFS($FB01) //  YOFFS - Light Pen Y Calibration Offset %RYYYYYYY:                 1B/RW
                       // Y = Y Calibration Offset (7-Bit)
                       // R = Reserved For Future Use (Mask From Reads & Do Not Set)

constant DRVINF($FB21) // DRVINF - Drive Info:                                               8B/RW
constant DRCNT1($FB21) // DRCNT1 - Number Of Drives Connected To Disk Interface 1            1B/RW
constant DRSAD1($FB22) // DRSAD1 - Slot Address Of Disk Interface 1                          1B/RW
constant DRCNT2($FB23) // DRCNT2 - Number Of Drives Connected To Disk Interface 2            1B/RW
constant DRSAD2($FB24) // DRSAD2 - Slot Address Of Disk Interface 2                          1B/RW
constant DRCNT3($FB25) // DRCNT3 - Number Of Drives Connected To Disk Interface 3            1B/RW
constant DRSAD3($FB26) // DRSAD3 - Slot Address Of Disk Interface 3                          1B/RW
constant DRCNT4($FB27) // DRCNT4 - Number Of Drives Connected To Disk Interface 4            1B/RW
constant DRSAD4($FB28) // DRSAD4 - Slot Address Of Disk Interface 4                          1B/RW

constant EXPTBL($FCC1) // EXPTBL - Expansion Slot 0..3 Table:                                4B/RW
constant EXSAD0($FCC1) // EXSAD0 - Slot 0: $80 = Expanded, 0 = Not Expanded (Main Slot)      1B/RW
constant EXSAD1($FCC2) // EXSAD1 - Slot 1: $80 = Expanded, 0 = Not Expanded                  1B/RW
constant EXSAD2($FCC3) // EXSAD2 - Slot 2: $80 = Expanded, 0 = Not Expanded                  1B/RW
constant EXSAD3($FCC4) // EXSAD3 - Slot 3: $80 = Expanded, 0 = Not Expanded                  1B/RW

constant SLTTBL($FCC5) // SLTTBL - Mirror Of Slot 0..3 Secondary Slot Selection Registers:   4B/RW
constant SLMIR0($FCC5) // SLMIR0 - Slot 0: Mirror Of Secondary Slot Selection Register       1B/RW
constant SLMIR1($FCC6) // SLMIR1 - Slot 1: Mirror Of Secondary Slot Selection Register       1B/RW
constant SLMIR2($FCC7) // SLMIR2 - Slot 2: Mirror Of Secondary Slot Selection Register       1B/RW
constant SLMIR3($FCC8) // SLMIR3 - Slot 3: Mirror Of Secondary Slot Selection Register       1B/RW

constant RG8SAV($FFE7) // RG8SAV - Mirror Of VDP Register  8 (Basic:  VDP(9))                1B/RW
constant RG9SAV($FFE8) // RG9SAV - Mirror Of VDP Register  9 (Basic: VDP(10))                1B/RW
constant RG10SA($FFE9) // RG10SA - Mirror Of VDP Register 10 (Basic: VDP(11))                1B/RW
constant RG11SA($FFEA) // RG11SA - Mirror Of VDP Register 11 (Basic: VDP(12))                1B/RW
constant RG12SA($FFEB) // RG12SA - Mirror Of VDP Register 12 (Basic: VDP(13))                1B/RW
constant RG13SA($FFEC) // RG13SA - Mirror Of VDP Register 13 (Basic: VDP(14))                1B/RW
constant RG14SA($FFED) // RG14SA - Mirror Of VDP Register 14 (Basic: VDP(15))                1B/RW
constant RG15SA($FFEE) // RG15SA - Mirror Of VDP Register 15 (Basic: VDP(16))                1B/RW
constant RG16SA($FFEF) // RG16SA - Mirror Of VDP Register 16 (Basic: VDP(17))                1B/RW
constant RG17SA($FFF0) // RG17SA - Mirror Of VDP Register 17 (Basic: VDP(18))                1B/RW
constant RG18SA($FFF1) // RG18SA - Mirror Of VDP Register 18 (Basic: VDP(19))                1B/RW
constant RG19SA($FFF2) // RG19SA - Mirror Of VDP Register 19 (Basic: VDP(20))                1B/RW
constant RG20SA($FFF3) // RG20SA - Mirror Of VDP Register 20 (Basic: VDP(21))                1B/RW
constant RG21SA($FFF4) // RG21SA - Mirror Of VDP Register 21 (Basic: VDP(22))                1B/RW
constant RG22SA($FFF5) // RG22SA - Mirror Of VDP Register 22 (Basic: VDP(23))                1B/RW
constant RG23SA($FFF6) // RG23SA - Mirror Of VDP Register 23 (Basic: VDP(24))                1B/RW
constant ROMSLT($FFF7) // ROMSLT - Main BIOS Slot ID (MSX2 Upwards)                          1B/RW
constant RG25SA($FFFA) // RG25SA - Mirror Of VDP Register 25 (Basic: VDP(26))                1B/RW
constant RG26SA($FFFB) // RG26SA - Mirror Of VDP Register 26 (Basic: VDP(27))                1B/RW
constant RG27SA($FFFC) // RG27SA - Mirror Of VDP Register 27 (Basic: VDP(28))                1B/RW

constant SEL2ND($FFFF) // SEL2ND - Secondary Slot Select (IF Slot Is Expanded) %DDCCBBAA:    1B/RW
                       // A = Page 0: Secondary Slot ($0000..$3FFF) (2-Bit)
                       // B = Page 1: Secondary Slot ($4000..$7FFF) (2-Bit)
                       // C = Page 2: Secondary Slot ($8000..$BFFF) (2-Bit)
                       // D = Page 3: Secondary Slot ($C000..$FFFF) (2-Bit)
                       // Reading Returns Inverse Of Current Subslot Selection
                       // Values Are Mirrored In SLTTBL For Convenience
                       // Note Each Expanded Primary Slot Has Its Own Register
                       // To Access A Specific Primary Slot Register Select It In Page 3