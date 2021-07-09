
#include <Windows.h>
#include <stdio.h>
#include <string.h>

#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")

#include "XInputController.h"

typedef struct tCONTROLLER_STATE{
	XINPUT_STATE state;
	BYTE bConnected;
}CONTROLLER_STATE;

GamepadState gamepad_p1;
GamepadState gamepad_p2;
GamepadState gamepad_p3;
GamepadState gamepad_p4;

#define MAX_CONTROLLERS 1  // XInput handles up to 4 controllers 
#define INPUT_DEADZONE  ( 0.10f * 0x7FFFf )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.



CONTROLLER_STATE g_Controllers[MAX_CONTROLLERS];
WCHAR g_szMessage[4][1024] = { 0 };
HWND    g_hWnd;
BYTE    g_bDeadZoneOn = TRUE;


HRESULT UpdateControllerState()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &g_Controllers[i].state);

		if (dwResult == ERROR_SUCCESS)
			g_Controllers[i].bConnected = TRUE;
		else
			g_Controllers[i].bConnected = FALSE;
	}

	return S_OK;
}

void update_gamepad() {
	UpdateControllerState();
	// Just P1 For now.
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (g_Controllers[i].bConnected)
		{
			WORD wButtons = g_Controllers[i].state.Gamepad.wButtons;

			memset(&gamepad_p1, 0x00, sizeof(gamepad_p1));
			if (g_bDeadZoneOn)
			{
				// Zero value if thumbsticks are within the dead zone 
				if ((g_Controllers[i].state.Gamepad.sThumbLX < INPUT_DEADZONE &&
					g_Controllers[i].state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
					(g_Controllers[i].state.Gamepad.sThumbLY < INPUT_DEADZONE &&
						g_Controllers[i].state.Gamepad.sThumbLY > -INPUT_DEADZONE))
				{
					gamepad_p1.analog_lx = 0;
					gamepad_p1.analog_ly = 0;
				}
				else {
					gamepad_p1.analog_lx = g_Controllers[i].state.Gamepad.sThumbLX;
					gamepad_p1.analog_ly = g_Controllers[i].state.Gamepad.sThumbLY;
				}

				if ((g_Controllers[i].state.Gamepad.sThumbRX < INPUT_DEADZONE &&
					g_Controllers[i].state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
					(g_Controllers[i].state.Gamepad.sThumbRY < INPUT_DEADZONE &&
						g_Controllers[i].state.Gamepad.sThumbRY > -INPUT_DEADZONE))
				{
					gamepad_p1.analog_rx = 0;
					gamepad_p1.analog_ry = 0;
				}
				else {
					gamepad_p1.analog_rx = g_Controllers[i].state.Gamepad.sThumbRX;
					gamepad_p1.analog_ry = g_Controllers[i].state.Gamepad.sThumbRY;
				}
			}

			gamepad_p1.btn_a = (wButtons & XINPUT_GAMEPAD_A) ? TRUE : FALSE;
			gamepad_p1.btn_b = (wButtons & XINPUT_GAMEPAD_B) ? TRUE : FALSE;
			gamepad_p1.btn_x = (wButtons & XINPUT_GAMEPAD_X) ? TRUE : FALSE;
			gamepad_p1.btn_y = (wButtons & XINPUT_GAMEPAD_Y) ? TRUE : FALSE;
			gamepad_p1.btn_l1 = (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? TRUE : FALSE;
			gamepad_p1.btn_r1 = (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? TRUE : FALSE;
			gamepad_p1.btn_start = (wButtons & XINPUT_GAMEPAD_START) ? TRUE : FALSE;
			gamepad_p1.btn_back = (wButtons & XINPUT_GAMEPAD_BACK) ? TRUE : FALSE;
			gamepad_p1.dpad_down = (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? TRUE : FALSE;
			gamepad_p1.dpad_left = (wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? TRUE : FALSE;
			gamepad_p1.dpad_right = (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? TRUE : FALSE;
			gamepad_p1.dpad_up = (wButtons & XINPUT_GAMEPAD_DPAD_UP) ? TRUE : FALSE;
			gamepad_p1.btn_l3 = (wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? TRUE : FALSE;
			gamepad_p1.btn_r3 = (wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? TRUE : FALSE;
			gamepad_p1.trigger_l2 = g_Controllers[i].state.Gamepad.bLeftTrigger;
			gamepad_p1.trigger_r2 = g_Controllers[i].state.Gamepad.bRightTrigger;


		}

	}
}