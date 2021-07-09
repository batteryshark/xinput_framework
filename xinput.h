#pragma once

#pragma pack(1)
typedef struct tGamepadState {
	BYTE btn_a;
	BYTE btn_b;
	BYTE btn_x;
	BYTE btn_y;
	BYTE btn_l1;
	BYTE btn_r1;
	BYTE btn_l3;
	BYTE btn_r3;
	BYTE btn_start;
	BYTE btn_back;
	BYTE dpad_up;
	BYTE dpad_down;
	BYTE dpad_left;
	BYTE dpad_right;
	BYTE trigger_l2;
	BYTE trigger_r2;
	SHORT analog_lx;
	SHORT analog_ly;
	SHORT analog_rx;
	SHORT analog_ry;
}GamepadState;



extern GamepadState gamepad_p1;
extern GamepadState gamepad_p2;
extern GamepadState gamepad_p3;
extern GamepadState gamepad_p4;

void update_gamepad();
