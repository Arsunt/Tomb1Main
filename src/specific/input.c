#include "game/inv.h"
#include "game/lara.h"
#include "game/vars.h"
#include "specific/input.h"
#include "specific/shed.h"
#include "config.h"
#include "util.h"
#include <dinput.h>

#ifdef T1M_FEAT_GAMEPLAY
static int32_t camera_cooldown = 0;
#endif
#ifdef T1M_FEAT_INPUT
static int32_t medipack_cooldown = 0;
#endif

void S_UpdateInput()
{
    int32_t linput = 0;

    WinInReadJoystick();
    if (JoyYPos >= -8) {
        if (JoyYPos > 8) {
            linput = IN_RIGHT;
        }
    } else {
        linput = IN_LEFT;
    }
    if (JoyXPos <= 8) {
        if (JoyXPos < -8) {
            linput |= IN_FORWARD;
        }
    } else {
        linput |= IN_BACK;
    }

    if (Key_(0)) {
        linput |= IN_FORWARD;
    }
    if (Key_(1)) {
        linput |= IN_BACK;
    }
    if (Key_(2)) {
        linput |= IN_LEFT;
    }
    if (Key_(3)) {
        linput |= IN_RIGHT;
    }
    if (Key_(4)) {
        linput |= IN_STEPL;
    }
    if (Key_(5)) {
        linput |= IN_STEPR;
    }
    if (Key_(6)) {
        linput |= IN_SLOW;
    }
    if (Key_(7)) {
        linput |= IN_JUMP;
    }
    if (Key_(8)) {
        linput |= IN_ACTION;
    }
    if (Key_(9)) {
        linput |= IN_DRAW;
    }
    if (Key_(10)) {
        linput |= IN_LOOK;
    }
    if (Key_(11)) {
        linput |= IN_ROLL;
    }
    if (Key_(12) && Camera.type != CAM_CINEMATIC) {
        linput |= IN_OPTION;
    }
    if ((linput & IN_FORWARD) && (linput & IN_BACK)) {
        linput |= IN_ROLL;
    }

#ifdef T1M_FEAT_CHEATS
    if (T1MConfig.enable_cheats) {
        static int8_t is_stuff_cheat_key_pressed = 0;
        if (KeyData->keymap[DIK_I]) {
            if (!is_stuff_cheat_key_pressed) {
                is_stuff_cheat_key_pressed = 1;
                TRACE("enabling stuff cheat");
                linput |= IN_STUFFCHEAT;
            }
        } else {
            is_stuff_cheat_key_pressed = 0;
        }

        if (KeyData->keymap[DIK_O]) {
            linput |= IN_DOZYCHEAT;
        }
        if (KeyData->keymap[DIK_F10]) {
            LevelComplete = 1;
        }
        if (KeyData->keymap[DIK_F11] && LaraItem) {
            LaraItem->hit_points += linput & IN_SLOW ? -20 : 20;
            if (LaraItem->hit_points < 0) {
                LaraItem->hit_points = 0;
            }
            if (LaraItem->hit_points > LARA_HITPOINTS) {
                LaraItem->hit_points = LARA_HITPOINTS;
            }
        }
    }
#endif

#ifdef T1M_FEAT_INPUT
    if (T1MConfig.enable_numeric_keys) {
        if (KeyData->keymap[DIK_1] && Inv_RequestItem(O_GUN_ITEM)) {
            Lara.request_gun_type = LGT_PISTOLS;
        } else if (KeyData->keymap[DIK_2] && Inv_RequestItem(O_SHOTGUN_ITEM)) {
            Lara.request_gun_type = LGT_SHOTGUN;
        } else if (KeyData->keymap[DIK_3] && Inv_RequestItem(O_MAGNUM_ITEM)) {
            Lara.request_gun_type = LGT_MAGNUMS;
        } else if (KeyData->keymap[DIK_4] && Inv_RequestItem(O_UZI_ITEM)) {
            Lara.request_gun_type = LGT_UZIS;
        }

        if (medipack_cooldown > 0) {
            --medipack_cooldown;
        } else {
            if (KeyData->keymap[DIK_8] && Inv_RequestItem(O_MEDI_OPTION)) {
                UseItem(O_MEDI_OPTION);
                medipack_cooldown = 15; // half a second
            } else if (
                KeyData->keymap[DIK_9] && Inv_RequestItem(O_BIGMEDI_OPTION)) {
                UseItem(O_BIGMEDI_OPTION);
                medipack_cooldown = 15;
            }
        }
    }
#endif

    if (KeyData->keymap[DIK_RETURN] || (linput & IN_ACTION)) {
        linput |= IN_SELECT;
    }
    if (KeyData->keymap[DIK_ESCAPE]) {
        linput |= IN_DESELECT;
    }

    if ((linput & (IN_RIGHT | IN_LEFT)) == (IN_RIGHT | IN_LEFT)) {
        linput &= ~(IN_RIGHT | IN_LEFT);
    }

    if (!ModeLock && Camera.type != CAM_CINEMATIC) {
        if (KeyData->keymap[DIK_F5]) {
            linput |= IN_SAVE;
        } else if (KeyData->keymap[DIK_F6]) {
            linput |= IN_LOAD;
        }
    }

    if (IsHardwareRenderer) {
        if (KeyData->keymap[DIK_F3]) {
            AppSettings ^= 2u;
            do
                WinVidSpinMessageLoop();
            while (KeyData->keymap[DIK_F3]);
        }

        if (KeyData->keymap[DIK_F4]) {
            AppSettings ^= 1u;
            do {
                WinVidSpinMessageLoop();
            } while (KeyData->keymap[DIK_F4]);
        }

#ifdef T1M_FEAT_GAMEPLAY
        if (camera_cooldown > 0) {
            --camera_cooldown;
        } else if (KeyData->keymap[DIK_F1]) {
            camera_cooldown = 15; // half a second
            if (Camera.type == CAM_REALLY_FIXED) {
                Camera.type = CAM_CHASE;
            } else {
                Camera.type = CAM_REALLY_FIXED;
            }
        }
#endif

        if (KeyData->keymap[DIK_F2]) {
            AppSettings ^= 4u;
            do {
                WinVidSpinMessageLoop();
            } while (KeyData->keymap[DIK_F2]);
        }
    }

    Input = linput;
    return;
}

void T1MInjectSpecificInput()
{
    INJECT(0x0041E550, S_UpdateInput);
}
