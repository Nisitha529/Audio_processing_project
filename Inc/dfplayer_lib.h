#include <stdint.h>

#ifndef __DFPLAYER_LIB_H
#define __DFPLAYER_LIB_H

#define START_BYTE           0x7E
#define END_BYTE             0xEF
#define CMD_LEN              0x06
#define FEEDBACK_EN          0x01
#define VERSION_INFO         0xFF

#define CMD_NEXT             0x01
#define CMD_PREV             0x02
#define CMD_INC_VOL          0x04
#define CMD_DEC_VOL          0x05
#define CMD_SET_EQ           0x07
#define CMD_SET_PLAYBACKMODE 0x08
#define CMD_SET_PLAYBACKSRC  0x09
#define CMD_INIT_PARAMS      0x3F
#define CMD_SET_VOL          0x06
#define CMD_REPEAT_PLAY      0x11

#define CMD_RESET            0x0C
#define CMD_PLAYBACK         0x0D
#define CMD_PAUSE            0x0E

#define CMD_GET_TRACK        0x03

#define NULL_PARAM           0x00
#define PLAY_SOURCE_TF_CARD  0x02
#define NORMAL_VOL           20

typedef enum
{
	NORMAL       = 0x00,
	POP          = 0x01,
	ROCK         = 0x02,
	JAZZ         = 0x03,
	CLASSIC      = 0x04,
	BASE         = 0x05
}eq_type;

typedef enum
{
	REPEAT       = 0x00,
	FOLDERREPEAT = 0x01,
	SINGLEREPEAT = 0x02,
	SHUFFLE      = 0x03
}playbackmode_type;

typedef enum
{
	U            = 0x00,
	TF           = 0x01,
	AUX          = 0x02,
	SLEEP        = 0x03,
	FLASH_SR     = 0X04
}playbacksrc_type;

void dfplayer_init (uint8_t volume);
void dfplayer_play_first_track(void);
void dfplayer_play_next_track(void);
void dfplayer_play_prev_track(void);
void dfplayer_pause_track(void);
void dfplayer_playback_track(void);
void test_play_pause_btn(void);
void test_next_btn (void);
void test_prev_btn (void);

#endif
