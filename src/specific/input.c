#include "specific/input.h"

#include "config.h"
#include "game/inv.h"
#include "game/lara.h"
#include "global/vars.h"
#include "global/vars_platform.h"
#include "specific/smain.h"
#include "util.h"

#include <dinput.h>

#define KEY_DOWN(a) ((DIKeys[(a)] & 0x80) != 0)

int32_t OldInputDB = 0;

int16_t Layout[2][KEY_NUMBER_OF] = {
    // built-in controls
    {
        DIK_UP, // KEY_UP
        DIK_DOWN, // KEY_DOWN
        DIK_LEFT, // KEY_LEFT
        DIK_RIGHT, // KEY_RIGHT
        DIK_DELETE, // KEY_STEP_L
        DIK_NEXT, // KEY_STEP_R
        DIK_RSHIFT, // KEY_SLOW
        DIK_RMENU, // KEY_JUMP
        DIK_RCONTROL, // KEY_ACTION
        DIK_SPACE, // KEY_DRAW
        DIK_NUMPAD0, // KEY_LOOK
        DIK_END, // KEY_ROLL
        DIK_ESCAPE, // KEY_OPTION
        DIK_O, // KEY_FLY_CHEAT,
        DIK_I, // KEY_ITEM_CHEAT,
        DIK_X, // KEY_LEVEL_SKIP_CHEAT,
        DIK_P, // KEY_PAUSE,
        DIK_W, // KEY_CAMERA_UP
        DIK_S, // KEY_CAMERA_DOWN
        DIK_A, // KEY_CAMERA_LEFT
        DIK_D, // KEY_CAMERA_RIGHT
        DIK_SLASH, // KEY_CAMERA_RESET
    },

    // default user controls
    {
        DIK_NUMPAD8, // KEY_UP
        DIK_NUMPAD2, // KEY_DOWN
        DIK_NUMPAD4, // KEY_LEFT
        DIK_NUMPAD6, // KEY_RIGHT
        DIK_NUMPAD7, // KEY_STEP_L
        DIK_NUMPAD9, // KEY_STEP_R
        DIK_NUMPAD1, // KEY_SLOW
        DIK_ADD, // KEY_JUMP
        DIK_NUMPADENTER, // KEY_ACTION
        DIK_NUMPAD3, // KEY_DRAW
        DIK_NUMPAD0, // KEY_LOOK
        DIK_NUMPAD5, // KEY_ROLL
        DIK_DECIMAL, // KEY_OPTION
        DIK_O, // KEY_FLY_CHEAT,
        DIK_I, // KEY_ITEM_CHEAT,
        DIK_X, // KEY_LEVEL_SKIP_CHEAT,
        DIK_P, // KEY_PAUSE,
        DIK_W, // KEY_CAMERA_UP
        DIK_S, // KEY_CAMERA_DOWN
        DIK_A, // KEY_CAMERA_LEFT
        DIK_D, // KEY_CAMERA_RIGHT
        DIK_SLASH, // KEY_CAMERA_RESET
    }
};

int32_t ConflictLayout[KEY_NUMBER_OF] = { 0 };

static LPDIRECTINPUT8 DInput;
static LPDIRECTINPUTDEVICE8 IDID_SysKeyboard;
static uint8_t DIKeys[256];

static LPDIRECTINPUTDEVICE8 IDID_Joystick;

static int32_t MedipackCoolDown = 0;

static void DInputCreate();
static void DInputShutdown();
static void DInputKeyboardCreate();
static void DInputKeyboardRelease();
static void DInputKeyboardRead();
static int8_t Key_(KEY_NUMBER number);

static HRESULT DInputJoystickCreate();
static void DInputJoystickRelease();
static BOOL CALLBACK
EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE instance, LPVOID context);
static BOOL CALLBACK EnumCallback(LPCDIDEVICEINSTANCE instance, LPVOID context);

void InputInit()
{
    DInputCreate();
    DInputKeyboardCreate();
    if (T1MConfig.enable_xbox_one_controller) {
        DInputJoystickCreate();
    } else {
        IDID_Joystick = NULL;
    }
}

void InputShutdown()
{
    DInputKeyboardRelease();
    if (T1MConfig.enable_xbox_one_controller) {
        DInputJoystickRelease();
    }
    DInputShutdown();
}

static void DInputCreate()
{
    HRESULT result;

    result = DirectInput8Create(
        TombModule, DIRECTINPUT_VERSION, &IID_IDirectInput8, (LPVOID *)&DInput,
        NULL);

    if (result) {
        LOG_ERROR("DirectInput error code %x", result);
        ShowFatalError("Fatal DirectInput error!");
    }
}

static void DInputShutdown()
{
    if (DInput) {
        IDirectInput_Release(DInput);
        DInput = NULL;
    }
}

void DInputKeyboardCreate()
{
    HRESULT result;

    result = IDirectInput8_CreateDevice(
        DInput, &GUID_SysKeyboard, &IDID_SysKeyboard, NULL);
    if (result) {
        LOG_ERROR("DirectInput error code %x", result);
        ShowFatalError("Fatal DirectInput error!");
    }

    result = IDirectInputDevice_SetCooperativeLevel(
        IDID_SysKeyboard, TombHWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (result) {
        LOG_ERROR("DirectInput error code %x", result);
        ShowFatalError("Fatal DirectInput error!");
    }

    result =
        IDirectInputDevice_SetDataFormat(IDID_SysKeyboard, &c_dfDIKeyboard);
    if (result) {
        LOG_ERROR("DirectInput error code %x", result);
        ShowFatalError("Fatal DirectInput error!");
    }

    result = IDirectInputDevice_Acquire(IDID_SysKeyboard);
    if (result) {
        LOG_ERROR("DirectInput error code %x", result);
        ShowFatalError("Fatal DirectInput error!");
    }
}

void DInputKeyboardRelease()
{
    if (IDID_SysKeyboard) {
        IDirectInputDevice_Unacquire(IDID_SysKeyboard);
        IDirectInputDevice_Release(IDID_SysKeyboard);
        IDID_SysKeyboard = NULL;
    }
}

static void DInputKeyboardRead()
{
    while (IDirectInputDevice_GetDeviceState(
        IDID_SysKeyboard, sizeof(DIKeys), DIKeys)) {
        if (IDirectInputDevice_Acquire(IDID_SysKeyboard)) {
            memset(DIKeys, 0, sizeof(DIKeys));
            break;
        }
    }
}

static int8_t KbdKey(KEY_NUMBER number, int8_t user)
{
    uint16_t key =
        Layout[user ? INPUT_LAYOUT_USER : INPUT_LAYOUT_DEFAULT][number];
    if KEY_DOWN (key) {
        return TRUE;
    }
    if (key == DIK_LCONTROL) {
        return KEY_DOWN(DIK_RCONTROL);
    }
    if (key == DIK_RCONTROL) {
        return KEY_DOWN(DIK_LCONTROL);
    }
    if (key == DIK_LSHIFT) {
        return KEY_DOWN(DIK_RSHIFT);
    }
    if (key == DIK_RSHIFT) {
        return KEY_DOWN(DIK_LSHIFT);
    }
    if (key == DIK_LMENU) {
        return KEY_DOWN(DIK_RMENU);
    }
    if (key == DIK_RMENU) {
        return KEY_DOWN(DIK_LMENU);
    }
    return 0;
}

static int8_t Key_(KEY_NUMBER number)
{
    return KbdKey(number, 1) || (!ConflictLayout[number] && KbdKey(number, 0));
}

int16_t KeyGet()
{
    for (int16_t key = 0; key < 256; key++) {
        if (KEY_DOWN(key)) {
            return key;
        }
    }
    return -1;
}

static HRESULT DInputJoystickCreate()
{
    HRESULT result;

    // Look for the first simple joystick we can find.
    if (FAILED(
            result = IDirectInput8_EnumDevices(
                DInput, DI8DEVCLASS_GAMECTRL, EnumCallback, NULL,
                DIEDFL_ATTACHEDONLY))) {
        LOG_ERROR(
            "Error while calling IDirectInput8_EnumDevices: 0x%lx", result);
        return result;
    }

    // Make sure we got a joystick
    if (IDID_Joystick == NULL) {
        LOG_ERROR("Joystick not found.\n");
        return E_FAIL;
    }
    LOG_INFO("Joystick found.\n");

    DIDEVCAPS capabilities;
    // request simple joystick format 2
    if (FAILED(
            result = IDirectInputDevice_SetDataFormat(
                IDID_Joystick, &c_dfDIJoystick2))) {
        LOG_ERROR(
            "Error while calling IDirectInputDevice_SetDataFormat: 0x%lx",
            result);
        DInputJoystickRelease();
        return result;
    }

    // don't request exclusive access
    if (FAILED(
            result = IDirectInputDevice_SetCooperativeLevel(
                IDID_Joystick, NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
        LOG_ERROR(
            "Error while calling IDirectInputDevice_SetCooperativeLevel: 0x%lx",
            result);
        DInputJoystickRelease();
        return result;
    }

    // get axis count, we should know what it is but best to ask
    capabilities.dwSize = sizeof(DIDEVCAPS);
    if (FAILED(
            result = IDirectInputDevice_GetCapabilities(
                IDID_Joystick, &capabilities))) {
        LOG_ERROR(
            "Error while calling IDirectInputDevice_GetCapabilities: 0x%lx",
            result);
        DInputJoystickRelease();
        return result;
    }

    // set the range we expect each axis to report back in
    if (FAILED(
            result = IDirectInputDevice_EnumObjects(
                IDID_Joystick, EnumAxesCallback, NULL, DIDFT_AXIS))) {
        LOG_ERROR(
            "Error while calling IDirectInputDevice_EnumObjects: 0x%lx",
            result);
        DInputJoystickRelease();
        return result;
    }
    return result;
}

static void DInputJoystickRelease()
{
    if (IDID_Joystick) {
        IDirectInputDevice_Unacquire(IDID_Joystick);
        IDirectInputDevice_Release(IDID_Joystick);
        IDID_Joystick = NULL;
    }
}

static BOOL CALLBACK
EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE instance, LPVOID context)
{
    HRESULT result;
    DIPROPRANGE propRange;

    propRange.diph.dwSize = sizeof(DIPROPRANGE);
    propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    propRange.diph.dwHow = DIPH_BYID;
    propRange.diph.dwObj = instance->dwType;
    propRange.lMin = -1024;
    propRange.lMax = 1024;

    // Set the range for the axis
    if (FAILED(
            result = IDirectInputDevice8_SetProperty(
                IDID_Joystick, DIPROP_RANGE, &propRange.diph))) {
        LOG_ERROR(
            "Error while calling IDirectInputDevice8_SetProperty: 0x%lx",
            result);
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

static BOOL CALLBACK EnumCallback(LPCDIDEVICEINSTANCEA instance, LPVOID context)
{
    HRESULT result;

    // Obtain an interface to the enumerated joystick.
    result = IDirectInput8_CreateDevice(
        DInput, &instance->guidInstance, &IDID_Joystick, NULL);

    if (FAILED(result)) {
        LOG_ERROR(
            "Error while calling IDirectInput8_CreateDevice: 0x%lx", result);
        return DIENUM_CONTINUE;
    }
    // we got one, it will do.
    return DIENUM_STOP;
}

static HRESULT DInputJoystickPoll(DIJOYSTATE2 *joystate)
{
    HRESULT result;

    if (!IDID_Joystick) {
        return S_OK;
    }

    // Poll the device to read the current state
    result = IDirectInputDevice8_Poll(IDID_Joystick);
    if (FAILED(result)) {
        // focus was lost, try to reaquire the device
        result = IDirectInputDevice8_Acquire(IDID_Joystick);
        while (result == DIERR_INPUTLOST) {
            result = IDirectInputDevice8_Acquire(IDID_Joystick);
        }

        // A fatal error? Return failure.
        if ((result == DIERR_INVALIDPARAM)
            || (result == DIERR_NOTINITIALIZED)) {
            LOG_ERROR(
                "Error while calling IDirectInputDevice8_Acquire: 0x%lx",
                result);
            return E_FAIL;
        }

        // If another application has control of this device, return
        // successfully.
        if (result == DIERR_OTHERAPPHASPRIO) {
            return S_OK;
        }
    }

    // Get the input's device state
    if (FAILED(
            result = IDirectInputDevice8_GetDeviceState(
                IDID_Joystick, sizeof(DIJOYSTATE2), joystate))) {
        return result; // The device should have been acquired during the Poll()
    }

    return S_OK;
}

void S_UpdateInput()
{
    int32_t linput = 0;

    DInputKeyboardRead();
    WinSpinMessageLoop();

    if (Key_(KEY_UP)) {
        linput |= IN_FORWARD;
    }
    if (Key_(KEY_DOWN)) {
        linput |= IN_BACK;
    }
    if (Key_(KEY_LEFT)) {
        linput |= IN_LEFT;
    }
    if (Key_(KEY_RIGHT)) {
        linput |= IN_RIGHT;
    }
    if (Key_(KEY_STEP_L)) {
        linput |= IN_STEPL;
    }
    if (Key_(KEY_STEP_R)) {
        linput |= IN_STEPR;
    }
    if (Key_(KEY_SLOW)) {
        linput |= IN_SLOW;
    }
    if (Key_(KEY_JUMP)) {
        linput |= IN_JUMP;
    }
    if (Key_(KEY_ACTION)) {
        linput |= IN_ACTION;
    }
    if (Key_(KEY_DRAW)) {
        linput |= IN_DRAW;
    }
    if (Key_(KEY_LOOK)) {
        linput |= IN_LOOK;
    }
    if (Key_(KEY_ROLL)) {
        linput |= IN_ROLL;
    }
    if (Key_(KEY_OPTION) && Camera.type != CAM_CINEMATIC) {
        linput |= IN_OPTION;
    }
    if (Key_(KEY_PAUSE)) {
        linput |= IN_PAUSE;
    }
    if ((linput & IN_FORWARD) && (linput & IN_BACK)) {
        linput |= IN_ROLL;
    }

    if (Key_(KEY_CAMERA_UP)) {
        linput |= IN_CAMERA_UP;
    }
    if (Key_(KEY_CAMERA_DOWN)) {
        linput |= IN_CAMERA_DOWN;
    }
    if (Key_(KEY_CAMERA_LEFT)) {
        linput |= IN_CAMERA_LEFT;
    }
    if (Key_(KEY_CAMERA_RIGHT)) {
        linput |= IN_CAMERA_RIGHT;
    }
    if (Key_(KEY_CAMERA_RESET)) {
        linput |= IN_CAMERA_RESET;
    }

    if (T1MConfig.enable_cheats) {
        static int8_t is_stuff_cheat_key_pressed = 0;
        if (Key_(KEY_ITEM_CHEAT)) {
            if (!is_stuff_cheat_key_pressed) {
                is_stuff_cheat_key_pressed = 1;
                linput |= IN_ITEM_CHEAT;
            }
        } else {
            is_stuff_cheat_key_pressed = 0;
        }

        if (Key_(KEY_FLY_CHEAT)) {
            linput |= IN_FLY_CHEAT;
        }
        if (Key_(KEY_LEVEL_SKIP_CHEAT)) {
            LevelComplete = 1;
        }
        if (KEY_DOWN(DIK_F11) && LaraItem) {
            LaraItem->hit_points += linput & IN_SLOW ? -20 : 20;
            if (LaraItem->hit_points < 0) {
                LaraItem->hit_points = 0;
            }
            if (LaraItem->hit_points > LARA_HITPOINTS) {
                LaraItem->hit_points = LARA_HITPOINTS;
            }
        }
    }

    if (T1MConfig.enable_numeric_keys) {
        if (KEY_DOWN(DIK_1) && Inv_RequestItem(O_GUN_ITEM)) {
            Lara.request_gun_type = LGT_PISTOLS;
        } else if (KEY_DOWN(DIK_2) && Inv_RequestItem(O_SHOTGUN_ITEM)) {
            Lara.request_gun_type = LGT_SHOTGUN;
        } else if (KEY_DOWN(DIK_3) && Inv_RequestItem(O_MAGNUM_ITEM)) {
            Lara.request_gun_type = LGT_MAGNUMS;
        } else if (KEY_DOWN(DIK_4) && Inv_RequestItem(O_UZI_ITEM)) {
            Lara.request_gun_type = LGT_UZIS;
        }

        if (MedipackCoolDown) {
            MedipackCoolDown--;
        } else {
            if (KEY_DOWN(DIK_8) && Inv_RequestItem(O_MEDI_OPTION)) {
                UseItem(O_MEDI_OPTION);
                MedipackCoolDown = FRAMES_PER_SECOND / 2;
            } else if (KEY_DOWN(DIK_9) && Inv_RequestItem(O_BIGMEDI_OPTION)) {
                UseItem(O_BIGMEDI_OPTION);
                MedipackCoolDown = FRAMES_PER_SECOND / 2;
            }
        }
    }

    if (KEY_DOWN(DIK_RETURN) || (linput & IN_ACTION)) {
        linput |= IN_SELECT;
    }
    if (KEY_DOWN(DIK_ESCAPE)) {
        linput |= IN_DESELECT;
    }

    if ((linput & (IN_RIGHT | IN_LEFT)) == (IN_RIGHT | IN_LEFT)) {
        linput &= ~(IN_RIGHT | IN_LEFT);
    }

    if (!ModeLock && Camera.type != CAM_CINEMATIC) {
        if (KEY_DOWN(DIK_F5)) {
            linput |= IN_SAVE;
        } else if (KEY_DOWN(DIK_F6)) {
            linput |= IN_LOAD;
        }
    }

    if (KEY_DOWN(DIK_F3)) {
        RenderSettings ^= RSF_BILINEAR;
        while (KEY_DOWN(DIK_F3)) {
            DInputKeyboardRead();
        }
    }

    if (KEY_DOWN(DIK_F4)) {
        RenderSettings ^= RSF_PERSPECTIVE;
        while (KEY_DOWN(DIK_F4)) {
            DInputKeyboardRead();
        }
    }

    if (KEY_DOWN(DIK_F2)) {
        RenderSettings ^= RSF_FPS;
        while (KEY_DOWN(DIK_F2)) {
            DInputKeyboardRead();
        }
    }

    if (IDID_Joystick) {
        DIJOYSTATE2 state;
        DInputJoystickPoll(&state);
        // check Y
        if (state.lY > 512) {
            linput |= IN_BACK;
        } else if (state.lY < -512) {
            linput |= IN_FORWARD;
        }
        // check X
        if (state.lX > 512) {
            linput |= IN_RIGHT;
        } else if (state.lX < -512) {
            linput |= IN_LEFT;
        }
        // check Z
        if (state.lZ > 512) {
            linput |= IN_STEPL;
        } else if (state.lZ < -512) {
            linput |= IN_STEPR;
        }

        // check 2nd stick X
        if (state.lRx > 512) {
            linput |= IN_CAMERA_RIGHT;
        } else if (state.lRx < -512) {
            linput |= IN_CAMERA_LEFT;
        }
        // check 2nd stick Y
        if (state.lRy > 512) {
            linput |= IN_CAMERA_DOWN;
        } else if (state.lRy < -512) {
            linput |= IN_CAMERA_UP;
        }

        // check buttons
        if (state.rgbButtons[0]) { // A
            linput |= IN_JUMP | IN_SELECT;
        }
        if (state.rgbButtons[1]) { // B
            linput |= IN_ROLL | IN_DESELECT;
        }
        if (state.rgbButtons[2]) { // X
            linput |= IN_ACTION | IN_SELECT;
        }
        if (state.rgbButtons[3]) { // Y
            linput |= IN_LOOK | IN_DESELECT;
        }
        if (state.rgbButtons[4]) { // LB
            linput |= IN_SLOW;
        }
        if (state.rgbButtons[5]) { // RB
            linput |= IN_DRAW;
        }
        if (state.rgbButtons[6]) { // back
            linput |= IN_OPTION;
        }
        if (state.rgbButtons[7]) { // start
            linput |= IN_PAUSE;
        }
        if (state.rgbButtons[9]) { // 2nd axis click
            linput |= IN_CAMERA_RESET;
        }
        // check dpad
        if (state.rgdwPOV[0] == 0) { // up
            linput |= IN_DRAW;
        }
    }

    Input = linput;

    return;
}

int32_t GetDebouncedInput(int32_t input)
{
    int32_t result = input & ~OldInputDB;
    OldInputDB = input;
    return result;
}

void T1MInjectSpecificInput()
{
    INJECT(0x0041E3E0, Key_);
    INJECT(0x0041E550, S_UpdateInput);
    INJECT(0x00437BC0, KeyGet);
}
