/*
	EPOCH Super Cassette Vision Emulator 'eSCV'

	Author : Takeda.Toshiya
	Date   : 2006.08.21 -

	Modified for Libretro-EmuSCV
	Author : MARCONATO Maxime (aka MaaaX)
	Date   : 2019-12-05 - 

	[ i/o ]
*/

#ifndef _EMUSCV_INC_VM_SCV_IO_H_
#define _EMUSCV_INC_VM_SCV_IO_H_

#include "../device.h"

class IO : public DEVICE
{
private:
	DEVICE* d_mem;
	DEVICE* d_sound;

	const uint8_t* key;
	const uint32_t* joy;
	uint8_t pa, pb, pc;

public:
	IO(VM_TEMPLATE* parent_vm, EMU* parent_emu) : DEVICE(parent_vm, parent_emu)
	{
		set_device_name(_T("I/O Bus"));
	}
	~IO() {}

	// common functions
	void initialize();
	void reset();
	void write_io8(uint32_t addr, uint32_t data);
	uint32_t read_io8(uint32_t addr);
	void save_state(STATE* state, bool max_size);
	bool load_state(STATE* state);

	// unique functions
	void set_context_mem(DEVICE* device)
	{
		d_mem = device;
	}
	void set_context_sound(DEVICE* device)
	{
		d_sound = device;
	}
};

#endif	// _EMUSCV_INC_VM_SCV_IO_H_
