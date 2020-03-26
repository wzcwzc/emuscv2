/*
	EPOCH Super Cassette Vision Emulator 'eSCV'

	Author : Takeda.Toshiya
	Date   : 2006.08.21 -

	[ virtual machine ]
*/

#ifndef _SCV_H_
#define _SCV_H_

#define DEVICE_NAME		"EPOCH/YENO Super Cassette Vision"
#define CONFIG_NAME 	"scv"

// Device informations for virtual machine
#define FRAMES_PER_SEC			60.0
#define LINES_PER_FRAME			262.0
#define CPU_CLOCKS				4000000.0
#define SCREEN_WIDTH			192.0
#define SCREEN_HEIGHT			216.0
// EPOCH console:	198x224
// YENO Console:	186x248 (including a black band of 3 pixels on right side and a black band of 8 pixels on the bottom)
// eSCV:			192x222	(-> 288x222)
// emuSCV:			192x216 (-> 864x648)
#define SCREEN_PIXELS			SCREEN_WIDTH * SCREEN_HEIGHT
#define SCREEN_COLORS			16	// Palette of 16 colors
#define SCREEN_ASPECT_WIDTH		SCREEN_WIDTH * 1.5	// 288
#define SCREEN_ASPECT_HEIGHT	SCREEN_HEIGHT		// 216
#define SCREEN_ASPECT_RATIO		SCREEN_ASPECT_WIDTH / SCREEN_ASPECT_HEIGHT	// Ratio 4/3
#define WINDOW_ZOOM_MAX			4.0
#define WINDOW_WIDTH			864.0
#define WINDOW_HEIGHT			648.0
#define WINDOW_PIXELS			WINDOW_WIDTH * WINDOW_HEIGHT
#define WINDOW_COLORS			256*256*256	// 16 Millions of colors
#define WINDOW_ASPECT_WIDTH		WINDOW_WIDTH
#define WINDOW_ASPECT_HEIGHT	WINDOW_HEIGHT
#define WINDOW_ASPECT_RATIO		WINDOW_ASPECT_WIDTH / WINDOW_ASPECT_HEIGHT	// Ratio 4/3

// memory wait
//#define UPD7801_MEMORY_WAIT

// device informations for win32
#define USE_CART			1
#define USE_SOUND_VOLUME	2
#define USE_JOYSTICK
#define USE_DEBUGGER
#define USE_STATE

#include "../../common.h"
#include "../../fileio.h"
#include "../vm_template.h"

#ifdef USE_SOUND_VOLUME
static const _TCHAR *sound_device_caption[] = {
	_T("PSG"), _T("PCM"),
};
#endif

class EMU;
class DEVICE;
class EVENT;

class UPD7801;

class IO;
class MEMORY;
class SOUND;
class VDP;

class VM : public VM_TEMPLATE
{
protected:
//	EMU* emu;

	// devices
	EVENT* event;

	UPD7801* cpu;

	IO* io;
	MEMORY* memory;
	SOUND* sound;
	VDP* vdp;

public:
	// ----------------------------------------
	// initialize
	// ----------------------------------------

	VM(EMU* parent_emu);
	~VM();

	// ----------------------------------------
	// for emulation class
	// ----------------------------------------

	// drive virtual machine
	void reset();
	void run();
	double get_frame_rate()
	{
		return FRAMES_PER_SEC;
	}

#ifdef USE_DEBUGGER
	// debugger
	DEVICE *get_cpu(int index);
#endif

	// draw screen
	void draw_screen();

	// sound generation
	void initialize_sound(int rate, int samples);
	uint16_t* create_sound(int* extra_frames);
	int get_sound_buffer_ptr();
#ifdef USE_SOUND_VOLUME
	void set_sound_device_volume(int ch, int decibel_l, int decibel_r);
#endif

	// user interface
	void open_cart(int drv, const _TCHAR* file_path);
	void close_cart(int drv);
	bool is_cart_inserted(int drv);
	bool is_frame_skippable();

	void update_config();
	bool process_state(FILEIO* state_fio, bool loading);

	// ----------------------------------------
	// for each device
	// ----------------------------------------

	// devices
	DEVICE* get_device(int id);
//	DEVICE* dummy;
//	DEVICE* first_device;
//	DEVICE* last_device;
};

#endif
