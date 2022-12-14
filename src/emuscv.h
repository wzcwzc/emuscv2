/*
	Libretro-EmuSCV

	Author : MARCONATO Maxime (aka MaaaX)
	Date   : 2019-12-05 - 

	[ Libretro core ]
*/

#ifndef _EMUSCV_INC_EMUSCV_H_
#define _EMUSCV_INC_EMUSCV_H_

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif
#include <math.h>

// Libraries
#include <libretro.h>
#include <SDL2/SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <zlib/zlib.h>
#include <unzip/unzip.h>
#include <lpng/png.h>
#include "common.h"
#include "state.h"

// SCV includes
#ifndef EMUSCV
	#define EMUSCV
#endif

class EMU;

#define EMUSCV_NAME					"Libretro-EmuSCV"
#define EMUSCV_DESCRIPTION			"EmuSCV is an open source emulator of EPOCH/YENO Super Cassette Vision under General Public Licence (GPL)."
#ifndef EMUSCV_VERSION_MAJOR
    #define EMUSCV_VERSION_MAJOR	"0"
#endif
#ifndef EMUSCV_VERSION_MINOR
    #define EMUSCV_VERSION_MINOR	"00"
#endif
#ifndef EMUSCV_VERSION_DATETIME
    #define EMUSCV_VERSION_DATETIME	"00000000000000"
#endif
#ifndef EMUSCV_VERSION
    #define EMUSCV_VERSION			"0.00.00000000000000"
#endif
#define EMUSCV_AUTHOR				"Maxime MARCONATO (aka MaaaX) - maxime@maaax.com"
#define EMUSCV_EXTENSIONS			"cart|bin|rom|0"//|zip"

// Input descriptions
#define EMUSCV_INPUTDESC_BUTTON_SELECT	"BUTTON SELECT"
#define EMUSCV_INPUTDESC_BUTTON_START	"BUTTON START"
#define EMUSCV_INPUTDESC_BUTTON_LEFT	"BUTTON LEFT"
#define EMUSCV_INPUTDESC_BUTTON_RIGHT	"BUTTON RIGHT"	// ┌───────┬──────┬─────────────┬──────┐
#define EMUSCV_INPUTDESC_BUTTON_UP		"BUTTON UP"		// │ POS.  │ SNES │ PLAYSTATION │ XBOX │
#define EMUSCV_INPUTDESC_BUTTON_DOWN	"BUTTON DOWN"	// ├───────┼──────┼─────────────┼──────┤
#define EMUSCV_INPUTDESC_BUTTON_1		"BUTTON 1"		// │ RIGHT │  A   │  CIRCLE     │  B   │
#define EMUSCV_INPUTDESC_BUTTON_2		"BUTTON 2"		// │ DOWN  │  B   │  CROSS      │  A   │
#define EMUSCV_INPUTDESC_BUTTON_3		"BUTTON 3"		// │ TOP   │  X   │  TRIANGLE   │  Y   │
#define EMUSCV_INPUTDESC_BUTTON_4		"BUTTON 4"		// │ LEFT  │  Y   │  SQUARE     │  X   │
#define EMUSCV_INPUTDESC_BUTTON_L1		"BUTTON L1"		// └───────┴──────┴─────────────┴──────┘
#define EMUSCV_INPUTDESC_BUTTON_R1		"BUTTON R1"
#define EMUSCV_INPUTDESC_BUTTON_L2		"BUTTON L2"
#define EMUSCV_INPUTDESC_BUTTON_R2		"BUTTON R2"
#define EMUSCV_INPUTDESC_BUTTON_L3		"BUTTON L3"
#define EMUSCV_INPUTDESC_BUTTON_R3		"BUTTON R3"
#define EMUSCV_INPUTDESC_ANALOG_LEFT_X	"ANALOG LEFT X"
#define EMUSCV_INPUTDESC_ANALOG_LEFT_Y	"ANALOG LEFT Y"
#define EMUSCV_INPUTDESC_ANALOG_RIGHT_X	"ANALOG RIGHT X"
#define EMUSCV_INPUTDESC_ANALOG_RIGHT_Y	"ANALOG RIGHT Y"

#define EMUSCV_AXIS_NEUTRAL_MAX			8192
#define EMUSCV_AXIS_NEUTRAL_MIN			-EMUSCV_AXIS_NEUTRAL_MAX

#define EMUSCV_NOISE_SAMPLES			16384

#define EMUSCV_CONTROLS_ALPHA			127

#define EMUSCV_KEYBOARD_ALPHA			200
#define EMUSCV_KEYBOARD_DELAY			100
#define EMUSCV_KEYBOARD_ALPHAKEYUP		80
#define EMUSCV_KEYBOARD_ALPHAKEYDOWN	160

#define EMUSCV_LOGO_ALPHA				180
#define EMUSCV_LOGO_DURATION			900


// /!\ Must be static
class cEmuSCV
{
	public:
		cEmuSCV();															// Class constructor
		~cEmuSCV();															// Class destructor
		void RetroSetEnvironment(retro_environment_t cb);					// Libretro: set the environment
		void RetroSetVideoRefresh(retro_video_refresh_t cb);				// Libretro: set the video refresh callback
		void RetroSetAudioSample(retro_audio_sample_t cb);					// Libretro: set the audio sample callback
		void RetroSetAudioSampleBatch(retro_audio_sample_batch_t cb);		// Libretro: set the audio batch callback
		void RetroSetInputPoll(retro_input_poll_t cb);						// Libretro: set the input poll callback
		void RetroSetInputState(retro_input_state_t cb);					// Libretro: set the input state callback
		unsigned RetroGetApiVersion();										// Libretro: return the version used by the core for compatibility check with the frontend
		unsigned RetroGetVideoRegion();										// Libretro: return the video standard used
		void RetroGetSystemInfo(struct retro_system_info *info);			// Libretro: get the system infos
		void RetroGetAudioVideoInfo(struct retro_system_av_info *info);		// Libretro: get the audio/video infos
		void RetroInit(retro_audio_callback_t retro_audio_cb, retro_audio_set_state_callback_t retro_audio_set_state_cb, retro_frame_time_callback_t retro_frame_time_cb);
																			// Libretro: initialize the core
		void RetroDeinit();													// Libretro: deinitialize the core
		void RetroSetControllerPortDevice(unsigned port, unsigned device);	// Libretro: set controller port device
		void RetroAudioSetStateCb(bool enable);								// Libretro: audio set state enable/disable callback
		void RetroFrameTimeCb(retro_usec_t usec);							// Libretro: retro frame time callback
		bool RetroLoadGame(const struct retro_game_info *info);				// Libretro: load game
		void RetroUnloadGame();												// Libretro: unload game
		void RetroRun();													// Libretro: run for only one frame
		void RetroReset(bool save_cart);									// Libretro: reset the Libretro core
		void RetroLoadSettings();											// Libretro: load core settings
		void RetroSaveSettings();											// Libretro: save core settings
		size_t RetroSaveStateSize();										// Libretro: return save state size
		void *RetroSaveStateData();											// Libretro: return save state data pointer
		bool RetroSaveState(void *data, size_t size);
		bool RetroLoadState(void *data, size_t size);

		retro_log_printf_t			RetroLogPrintf;
		retro_environment_t 		RetroEnvironment;
		retro_video_refresh_t		RetroVideoRefresh;
		retro_audio_sample_t		RetroAudioSample;
		retro_audio_sample_batch_t	RetroAudioSampleBatch;
		retro_input_poll_t			RetroInputPoll;
		retro_input_state_t			RetroInputState;

		bool retro_core_initialized;		// Is the libretro core initialized ?
		bool retro_audio_enable;			// Is the libretro audio enabled ?
		uint64_t retro_frame_counter;
		retro_usec_t retro_frame_time;

		bool retro_input_support_bitmask;
		bool retro_game_loaded;

		bool is_power_on;
		
		char retro_base_directory[_MAX_PATH];
		char retro_save_directory[_MAX_PATH];
		char retro_game_path[_MAX_PATH];

		int window_width_old;
		int window_height_old;
		double window_fps_old;

		EMU *escv_emu;	// eSCV emulation core

		SDL_Surface *frame_surface;			// SDL2 main frame surface
		SDL_Renderer *frame_renderer;		// SDL2 main frame renderer
		SDL_Surface *noise_surface;			// SDL2 TV static noise surface
		SDL_Renderer *noise_renderer;		// SDL2 TV static noise renderer
		SDL_Surface *keyboard_surface;		// SDL2 quick keyboard surface
		SDL_Renderer *keyboard_renderer;	// SDL2 quick keyboard renderer
		SDL_Surface *logo_surface;			// SDL2 EmuSCV logo surface
		SDL_Renderer *logo_renderer;		// SDL2 EmuSCV logo renderer
		SDL_Surface *recalbox_surface;		// SDL2 Recalbox logo surface
		SDL_Renderer *recalbox_renderer;	// SDL2 Recalbox logo renderer
		
		// To drive eSCV
		int run_frames_last;
		int run_frames_total;
		int draw_frames_total;

		bool key_pressed_0;
		bool key_pressed_1;
		bool key_pressed_2;
		bool key_pressed_3;
		bool key_pressed_4;
		bool key_pressed_5;
		bool key_pressed_6;
		bool key_pressed_7;
		bool key_pressed_8;
		bool key_pressed_9;
		bool key_pressed_cl;
		bool key_pressed_en;
		bool key_pressed_power;
		bool key_pressed_pause;
		bool key_pressed_reset;
		bool key_pressed_up;
		bool key_pressed_down;
		bool key_pressed_left;
		bool key_pressed_right;
		bool key_pressed_keyboard_stay_opened;
		bool key_pressed_keyboard_close;

		bool button_keyboard_pressed;
		bool button_menu_pressed;

		uint64_t start_up_counter_power;
		uint64_t start_up_counter_logo;

		bool is_keyboard_displayed;
		bool is_menu_displayed;
		uint8_t keyboard_x;
		uint8_t keyboard_y;
		int64_t keyboard_counter;

		int16_t sound_buffer_noise[EMUSCV_NOISE_SAMPLES];	// Mono noise
		size_t sound_buffer_noise_index;
		size_t sound_buffer_samples;
		size_t sound_buffer_size;

		bool CreateKeyboardSurface();
		bool DestroyKeyboardSurface();
		bool CreateLogoSurface();
		bool DestroyLogoSurface();
		bool CreateRecalboxSurface();
		bool DestroyRecalboxSurface();
		
		STATE state;

};

#endif	// _EMUSCV_INC_EMUSCV_H_
