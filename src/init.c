#include "init.h"

#include "global/vars.h"

// THIS IS AN AUTOGENERATED FILE.
// To generate it, run scripts/generate_init.

void T1MInit()
{
    GF.strings[GS_HEADING_INVENTORY] = "INVENTORY";
    GF.strings[GS_HEADING_GAME_OVER] = "GAME OVER";
    GF.strings[GS_HEADING_OPTION] = "OPTION";
    GF.strings[GS_HEADING_ITEMS] = "ITEMS";
    GF.strings[GS_PASSPORT_SELECT_LEVEL] = "Select Level";
    GF.strings[GS_PASSPORT_SELECT_MODE] = "Select Mode";
    GF.strings[GS_PASSPORT_MODE_NEW_GAME] = "New Game";
    GF.strings[GS_PASSPORT_MODE_NEW_GAME_PLUS] = "New Game+";
    GF.strings[GS_PASSPORT_MODE_JAPANESE_NEW_GAME] = "Japanese NG";
    GF.strings[GS_PASSPORT_MODE_JAPANESE_NEW_GAME_PLUS] = "Japanese NG+";
    GF.strings[GS_PASSPORT_NEW_GAME] = "New Game";
    GF.strings[GS_PASSPORT_LOAD_GAME] = "Load Game";
    GF.strings[GS_PASSPORT_SAVE_GAME] = "Save Game";
    GF.strings[GS_PASSPORT_EXIT_GAME] = "Exit Game";
    GF.strings[GS_PASSPORT_EXIT_TO_TITLE] = "Exit to Title";
    GF.strings[GS_DETAIL_SELECT_DETAIL] = "Select Detail";
    GF.strings[GS_DETAIL_LEVEL_HIGH] = "High";
    GF.strings[GS_DETAIL_LEVEL_MEDIUM] = "Medium";
    GF.strings[GS_DETAIL_LEVEL_LOW] = "Low";
    GF.strings[GS_DETAIL_PERSPECTIVE_FMT] = "Perspective     %s";
    GF.strings[GS_DETAIL_BILINEAR_FMT] = "Bilinear        %s";
    GF.strings[GS_DETAIL_UI_TEXT_SCALE_FMT] = "UI text scale   %.1f";
    GF.strings[GS_DETAIL_UI_BAR_SCALE_FMT] = "UI bar scale    %.1f";
    GF.strings[GS_DETAIL_VIDEO_MODE_FMT] = "Game Video Mode %s";
    GF.strings[GS_SOUND_SET_VOLUMES] = "Set Volumes";
    GF.strings[GS_CONTROL_DEFAULT_KEYS] = "Default Keys";
    GF.strings[GS_CONTROL_USER_KEYS] = "User Keys";
    GF.strings[GS_KEYMAP_RUN] = "Run";
    GF.strings[GS_KEYMAP_BACK] = "Back";
    GF.strings[GS_KEYMAP_LEFT] = "Left";
    GF.strings[GS_KEYMAP_RIGHT] = "Right";
    GF.strings[GS_KEYMAP_STEP_LEFT] = "Step Left";
    GF.strings[GS_KEYMAP_STEP_RIGHT] = "Step Right";
    GF.strings[GS_KEYMAP_WALK] = "Walk";
    GF.strings[GS_KEYMAP_JUMP] = "Jump";
    GF.strings[GS_KEYMAP_ACTION] = "Action";
    GF.strings[GS_KEYMAP_DRAW_WEAPON] = "Draw Weapon";
    GF.strings[GS_KEYMAP_LOOK] = "Look";
    GF.strings[GS_KEYMAP_ROLL] = "Roll";
    GF.strings[GS_KEYMAP_INVENTORY] = "Inventory";
    GF.strings[GS_KEYMAP_PAUSE] = "Pause";
    GF.strings[GS_KEYMAP_FLY_CHEAT] = "Fly cheat";
    GF.strings[GS_KEYMAP_ITEM_CHEAT] = "Item cheat";
    GF.strings[GS_KEYMAP_LEVEL_SKIP_CHEAT] = "Level skip";
    GF.strings[GS_KEYMAP_CAMERA_UP] = "Camera Up";
    GF.strings[GS_KEYMAP_CAMERA_DOWN] = "Camera Down";
    GF.strings[GS_KEYMAP_CAMERA_LEFT] = "Camera Left";
    GF.strings[GS_KEYMAP_CAMERA_RIGHT] = "Camera Right";
    GF.strings[GS_KEYMAP_CAMERA_RESET] = "Reset Camera";
    GF.strings[GS_STATS_TIME_TAKEN_FMT] = "TIME TAKEN %s";
    GF.strings[GS_STATS_SECRETS_FMT] = "SECRETS %d OF %d";
    GF.strings[GS_STATS_PICKUPS_FMT] = "PICKUPS %d";
    GF.strings[GS_STATS_KILLS_FMT] = "KILLS %d";
    GF.strings[GS_PAUSE_PAUSED] = "Paused";
    GF.strings[GS_PAUSE_EXIT_TO_TITLE] = "Exit to title?";
    GF.strings[GS_PAUSE_CONTINUE] = "Continue";
    GF.strings[GS_PAUSE_QUIT] = "Quit";
    GF.strings[GS_PAUSE_ARE_YOU_SURE] = "Are you sure?";
    GF.strings[GS_PAUSE_YES] = "Yes";
    GF.strings[GS_PAUSE_NO] = "No";
    GF.strings[GS_MISC_ON] = "On";
    GF.strings[GS_MISC_OFF] = "Off";
    GF.strings[GS_MISC_EMPTY_SLOT_FMT] = "- EMPTY SLOT %d -";
    GF.strings[GS_MISC_DEMO_MODE] = "Demo Mode";
    GF.strings[GS_INV_ITEM_MEDI] = "Small Medi Pack";
    GF.strings[GS_INV_ITEM_BIG_MEDI] = "Large Medi Pack";
    GF.strings[GS_INV_ITEM_PUZZLE1] = "Puzzle";
    GF.strings[GS_INV_ITEM_PUZZLE2] = "Puzzle";
    GF.strings[GS_INV_ITEM_PUZZLE3] = "Puzzle";
    GF.strings[GS_INV_ITEM_PUZZLE4] = "Puzzle";
    GF.strings[GS_INV_ITEM_KEY1] = "Key";
    GF.strings[GS_INV_ITEM_KEY2] = "Key";
    GF.strings[GS_INV_ITEM_KEY3] = "Key";
    GF.strings[GS_INV_ITEM_KEY4] = "Key";
    GF.strings[GS_INV_ITEM_PICKUP1] = "Pickup";
    GF.strings[GS_INV_ITEM_PICKUP2] = "Pickup";
    GF.strings[GS_INV_ITEM_LEADBAR] = "Lead Bar";
    GF.strings[GS_INV_ITEM_SCION] = "Scion";
    GF.strings[GS_INV_ITEM_PISTOLS] = "Pistols";
    GF.strings[GS_INV_ITEM_SHOTGUN] = "Shotgun";
    GF.strings[GS_INV_ITEM_MAGNUM] = "Magnums";
    GF.strings[GS_INV_ITEM_UZI] = "Uzis";
    GF.strings[GS_INV_ITEM_GRENADE] = "Grenade";
    GF.strings[GS_INV_ITEM_PISTOL_AMMO] = "Pistol Clips";
    GF.strings[GS_INV_ITEM_SHOTGUN_AMMO] = "Shotgun Shells";
    GF.strings[GS_INV_ITEM_MAGNUM_AMMO] = "Magnum Clips";
    GF.strings[GS_INV_ITEM_UZI_AMMO] = "Uzi Clips";
    GF.strings[GS_INV_ITEM_COMPASS] = "Compass";
    GF.strings[GS_INV_ITEM_GAME] = "Game";
    GF.strings[GS_INV_ITEM_DETAILS] = "Detail Levels";
    GF.strings[GS_INV_ITEM_SOUND] = "Sound";
    GF.strings[GS_INV_ITEM_CONTROLS] = "Controls";
    GF.strings[GS_INV_ITEM_GAMMA] = "Gamma";
    GF.strings[GS_INV_ITEM_LARAS_HOME] = "Lara's Home";
}
