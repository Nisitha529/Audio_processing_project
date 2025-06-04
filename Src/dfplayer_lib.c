#include <stdio.h>
#include "dfplayer_lib.h"
#include "circular_buffer.h"
#include "bsp.h"
#include "timebase.h"

portType debug_port     = DEBUG_PORT;
portType slave_dev_port = SLAVE_DEV_PORT;

#define  dfplayer_port     slave_dev_port
#define  CMD_FRAME_LEN     10
#define  SHORT_DLY         200
#define  LONG_DLY          500
#define  START_REPEAT_PLAY 0x01

bool IS_PLAYING = false;

void dfplayer_send_cmd (uint8_t cmd, uint8_t para1, uint8_t para2)
{
	uint16_t checksum;

	// Clear the buffer
	buffer_clear(dfplayer_port);

	checksum = VERSION_INFO + CMD_LEN + cmd + FEEDBACK_EN + para1 + para2;
	// Calculating 2's complement for checksum
	checksum = ~checksum + 1;

	uint8_t cmd_frame[CMD_FRAME_LEN] = {START_BYTE, VERSION_INFO, CMD_LEN, cmd, FEEDBACK_EN, para1, para2, (checksum >> 8) & 0x00FF, checksum & 0x00FF, END_BYTE};

	buffer_send_byte(cmd_frame, sizeof(cmd_frame), dfplayer_port);
}

void dfplayer_init (uint8_t volume)
{
    // Set the init params
	dfplayer_send_cmd(CMD_INIT_PARAMS, NULL_PARAM, PLAY_SOURCE_TF_CARD);
	delay(SHORT_DLY);

	// Set volume
	dfplayer_send_cmd(CMD_SET_VOL, NULL_PARAM, NORMAL_VOL);
	delay(LONG_DLY);
}

void dfplayer_play_first_track(void)
{
	dfplayer_send_cmd(CMD_REPEAT_PLAY, NULL_PARAM, START_REPEAT_PLAY);
	delay(SHORT_DLY);
}

void dfplayer_play_next_track(void)
{
	dfplayer_send_cmd(CMD_NEXT, NULL_PARAM, NULL_PARAM);
	delay(SHORT_DLY);
}

void dfplayer_play_prev_track(void)
{
	dfplayer_send_cmd(CMD_PREV, NULL_PARAM, NULL_PARAM);
	delay(SHORT_DLY);
}

void dfplayer_pause_track(void)
{
	dfplayer_send_cmd(CMD_PAUSE, NULL_PARAM, NULL_PARAM);
	delay(SHORT_DLY);
}

void dfplayer_playback_track(void)
{
	dfplayer_send_cmd(CMD_PLAYBACK, NULL_PARAM, TF);
	delay(SHORT_DLY);
}

void test_play_pause_btn(void)
{
	if (get_btn_state())
	{
		// Handle debounce
		while (get_btn_state()){}

		// Check play/pause state
		if (IS_PLAYING)
		{
			dfplayer_pause_track();
			IS_PLAYING = false;
		}
		else
		{
			dfplayer_playback_track();
			IS_PLAYING = true;
		}
	}
}

void test_next_btn (void)
{
	if (get_btn_state())
	{
		while(get_btn_state()){}
		dfplayer_play_next_track();
	}
}

void test_prev_btn (void)
{
	if (get_btn_state())
	{
		while(get_btn_state()){}
		dfplayer_play_prev_track();
	}
}






