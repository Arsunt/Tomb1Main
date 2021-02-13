#include "data.h"
#include "effects.h"

void __cdecl FxChainBlock(ITEM_INFO* item)
{
    if (FlipTimer == 0) {
        SoundEffect(173, NULL, 0);
    }

    FlipTimer++;
    if (FlipTimer == 55) {
        SoundEffect(33, NULL, 0);
        FlipEffect = -1;
    }
}

void TR1MInjectEffects()
{
    INJECT(0x0041AD00, FxChainBlock);
}