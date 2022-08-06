#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

/**
 * <code>
 * Bits: <br/>
 * 7 6 5 4  3 2 1 0 <br/>
 * x x x x  x x x x <br/>
 * | | | |  | | | | <br/>
 * | | | |  | | | O--> Payload size (LSB) <br/>
 * | | | |  | | O----> Payload size <br/>
 * | | | |  | O------> Payload size (MSB) <br/>
 * | | | |  O--------> Mod key <br/>
 * | | | | <br/>
 * | | | O-----------> Command (LSB) <br/>
 * | | O-------------> Command <br/>
 * | O---------------> Command (MSB) <br/>
 * O-----------------> Extended command flag <br/>
*/

// Mask for extended command check
#define CMD_EXTENDED            0b10000000
#define CMD_MASK                0b01110000
#define CMD_MOD_KEY_MASK        0b00001000
#define CMD_PAYLOAD_SIZE_MASK   0b00000111
#define CMD_COMMAND_OFFSET_BITS 4
#define CMD_PAYLOAD_SIZE_NUMBER_OF_BITS 3

// End command
#define CMD_END 0x00

// Commands for keys
#define CMD_KEY_DOWN 0x01
#define CMD_KEY_UP 0x02
#define CMD_KEY_PRESS 0x03

// Commands for delay
#define CMD_DELAY_SHORT 0x04
#define CMD_DELAY_LONG 0x05
#define CMD_DELAY_LONG_LONG 0x06

// Extended commands
#define CMD_KEY_STREAM (CMD_EXTENDED | 0x01)
#define CMD_SELECT_PROFILE (CMD_EXTENDED | 0x02)

#endif