#ifndef FONT_H__
#define FONT_H__

// make these functions:
// void drawChar(...);
// void drawString(...);

// lookup table for all of the ascii characters
// i changed the table to have the 6th column be the ascii value of the character
static const char ASCII[96][6] = {
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x20} // 20  (space) 0
,{0x00, 0x00, 0x5f, 0x00, 0x00, 0x21} // 21 !        1 
,{0x00, 0x07, 0x00, 0x07, 0x00, 0x22} // 22 "        2
,{0x14, 0x7f, 0x14, 0x7f, 0x14, 0x23} // 23 #        3
,{0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x24} // 24 $        4  
,{0x23, 0x13, 0x08, 0x64, 0x62, 0x25} // 25 %        5
,{0x36, 0x49, 0x55, 0x22, 0x50, 0x26} // 26 &        6
,{0x00, 0x05, 0x03, 0x00, 0x00, 0x27} // 27 '        7 
,{0x00, 0x1c, 0x22, 0x41, 0x00, 0x28} // 28 (        8
,{0x00, 0x41, 0x22, 0x1c, 0x00, 0x29} // 29 )        9
,{0x14, 0x08, 0x3e, 0x08, 0x14, 0x2a} // 2a *        10
,{0x08, 0x08, 0x3e, 0x08, 0x08, 0x2b} // 2b +        11
,{0x00, 0x50, 0x30, 0x00, 0x00, 0x2c} // 2c ,        12
,{0x08, 0x08, 0x08, 0x08, 0x08, 0x2d} // 2d -        13
,{0x00, 0x60, 0x60, 0x00, 0x00, 0x2e} // 2e .        14
,{0x20, 0x10, 0x08, 0x04, 0x02, 0x2f} // 2f /        15
,{0x3e, 0x51, 0x49, 0x45, 0x3e, 0x30} // 30 0        16
,{0x00, 0x42, 0x7f, 0x40, 0x00, 0x31} // 31 1        17
,{0x42, 0x61, 0x51, 0x49, 0x46, 0x32} // 32 2        18
,{0x21, 0x41, 0x45, 0x4b, 0x31, 0x33} // 33 3        19
,{0x18, 0x14, 0x12, 0x7f, 0x10, 0x34} // 34 4        20
,{0x27, 0x45, 0x45, 0x45, 0x39, 0x35} // 35 5        21
,{0x3c, 0x4a, 0x49, 0x49, 0x30, 0x36} // 36 6        22
,{0x01, 0x71, 0x09, 0x05, 0x03, 0x37} // 37 7        23
,{0x36, 0x49, 0x49, 0x49, 0x36, 0x38} // 38 8        24
,{0x06, 0x49, 0x49, 0x29, 0x1e, 0x39} // 39 9        25
,{0x00, 0x36, 0x36, 0x00, 0x00, 0x3a} // 3a :        26
,{0x00, 0x56, 0x36, 0x00, 0x00, 0x3b} // 3b ;        27
,{0x08, 0x14, 0x22, 0x41, 0x00, 0x3c} // 3c <        28  
,{0x14, 0x14, 0x14, 0x14, 0x14, 0x3d} // 3d =        29
,{0x00, 0x41, 0x22, 0x14, 0x08, 0x3e} // 3e >        30
,{0x02, 0x01, 0x51, 0x09, 0x06, 0x3f} // 3f ?        31
,{0x32, 0x49, 0x79, 0x41, 0x3e, 0x40} // 40 @        32 
,{0x7e, 0x11, 0x11, 0x11, 0x7e, 0x41} // 41 A        33
,{0x7f, 0x49, 0x49, 0x49, 0x36, 0x42} // 42 B        34
,{0x3e, 0x41, 0x41, 0x41, 0x22, 0x43} // 43 C        35
,{0x7f, 0x41, 0x41, 0x22, 0x1c, 0x44} // 44 D        36 
,{0x7f, 0x49, 0x49, 0x49, 0x41, 0x45} // 45 E        37
,{0x7f, 0x09, 0x09, 0x09, 0x01, 0x46} // 46 F        38
,{0x3e, 0x41, 0x49, 0x49, 0x7a, 0x47} // 47 G        39
,{0x7f, 0x08, 0x08, 0x08, 0x7f, 0x48} // 48 H        40
,{0x00, 0x41, 0x7f, 0x41, 0x00, 0x49} // 49 I        41
,{0x20, 0x40, 0x41, 0x3f, 0x01, 0x4a} // 4a J        42 
,{0x7f, 0x08, 0x14, 0x22, 0x41, 0x4b} // 4b K        43
,{0x7f, 0x40, 0x40, 0x40, 0x40, 0x4c} // 4c L        44
,{0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x4d} // 4d M        45
,{0x7f, 0x04, 0x08, 0x10, 0x7f, 0x4e} // 4e N        46
,{0x3e, 0x41, 0x41, 0x41, 0x3e, 0x4f} // 4f O        47
,{0x7f, 0x09, 0x09, 0x09, 0x06, 0x50} // 50 P        48 
,{0x3e, 0x41, 0x51, 0x21, 0x5e, 0x51} // 51 Q        49
,{0x7f, 0x09, 0x19, 0x29, 0x46, 0x52} // 52 R        50 
,{0x46, 0x49, 0x49, 0x49, 0x31, 0x53} // 53 S        51 
,{0x01, 0x01, 0x7f, 0x01, 0x01, 0x54} // 54 T        52
,{0x3f, 0x40, 0x40, 0x40, 0x3f, 0x55} // 55 U        53
,{0x1f, 0x20, 0x40, 0x20, 0x1f, 0x56} // 56 V        54
,{0x3f, 0x40, 0x38, 0x40, 0x3f, 0x57} // 57 W        55 
,{0x63, 0x14, 0x08, 0x14, 0x63, 0x58} // 58 X        56 
,{0x07, 0x08, 0x70, 0x08, 0x07, 0x59} // 59 Y        57 
,{0x61, 0x51, 0x49, 0x45, 0x43, 0x5a} // 5a Z        58
,{0x00, 0x7f, 0x41, 0x41, 0x00, 0x5b} // 5b [        59 
,{0x02, 0x04, 0x08, 0x10, 0x20, 0x5c} // 5c ?        60
,{0x00, 0x41, 0x41, 0x7f, 0x00, 0x5d} // 5d ]        61
,{0x04, 0x02, 0x01, 0x02, 0x04, 0x5e} // 5e ^        62
,{0x40, 0x40, 0x40, 0x40, 0x40, 0x5f} // 5f _        63
,{0x00, 0x01, 0x02, 0x04, 0x00, 0x60} // 60 `        64 
,{0x20, 0x54, 0x54, 0x54, 0x78, 0x61} // 61 a        65
,{0x7f, 0x48, 0x44, 0x44, 0x38, 0x62} // 62 b        66
,{0x38, 0x44, 0x44, 0x44, 0x20, 0x63} // 63 c        67
,{0x38, 0x44, 0x44, 0x48, 0x7f, 0x64} // 64 d        68
,{0x38, 0x54, 0x54, 0x54, 0x18, 0x65} // 65 e        69 
,{0x08, 0x7e, 0x09, 0x01, 0x02, 0x66} // 66 f        70
,{0x0c, 0x52, 0x52, 0x52, 0x3e, 0x67} // 67 g        71
,{0x7f, 0x08, 0x04, 0x04, 0x78, 0x68} // 68 h        72 
,{0x00, 0x44, 0x7d, 0x40, 0x00, 0x69} // 69 i        73
,{0x20, 0x40, 0x44, 0x3d, 0x00, 0x6a} // 6a j        74  
,{0x7f, 0x10, 0x28, 0x44, 0x00, 0x6b} // 6b k        75
,{0x00, 0x41, 0x7f, 0x40, 0x00, 0x6c} // 6c l        76
,{0x7c, 0x04, 0x18, 0x04, 0x78, 0x6d} // 6d m        77 
,{0x7c, 0x08, 0x04, 0x04, 0x78, 0x6e} // 6e n        78
,{0x38, 0x44, 0x44, 0x44, 0x38, 0x6f} // 6f o        79
,{0x7c, 0x14, 0x14, 0x14, 0x08, 0x70} // 70 p        80
,{0x08, 0x14, 0x14, 0x18, 0x7c, 0x71} // 71 q        81 
,{0x7c, 0x08, 0x04, 0x04, 0x08, 0x72} // 72 r        82
,{0x48, 0x54, 0x54, 0x54, 0x20, 0x73} // 73 s        83
,{0x04, 0x3f, 0x44, 0x40, 0x20, 0x74} // 74 t        84 
,{0x3c, 0x40, 0x40, 0x20, 0x7c, 0x75} // 75 u        85
,{0x1c, 0x20, 0x40, 0x20, 0x1c, 0x76} // 76 v        86
,{0x3c, 0x40, 0x30, 0x40, 0x3c, 0x77} // 77 w        87
,{0x44, 0x28, 0x10, 0x28, 0x44, 0x78} // 78 x        88
,{0x0c, 0x50, 0x50, 0x50, 0x3c, 0x79} // 79 y        89
,{0x44, 0x64, 0x54, 0x4c, 0x44, 0x7a} // 7a z        90
,{0x00, 0x08, 0x36, 0x41, 0x00, 0x7b} // 7b {        91
,{0x00, 0x00, 0x7f, 0x00, 0x00, 0x7c} // 7c |        92
,{0x00, 0x41, 0x36, 0x08, 0x00, 0x7d} // 7d }        93   
,{0x10, 0x08, 0x08, 0x10, 0x08, 0x7e} // 7e ?        94
,{0x00, 0x06, 0x09, 0x09, 0x06, 0x7f} // 7f ?        95
}; // end char ASCII[96][5]

int find_ascii(char c);
void drawChar(int index, int x, int y);
void drawString(char m[50], int x, int y);

#endif