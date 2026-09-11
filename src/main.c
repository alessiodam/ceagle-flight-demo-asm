#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#define BACKGROUND 0
#define FOREGROUND 1
#define ACCENT 2

static void palette(void)
{
    gfx_palette[BACKGROUND] = gfx_RGBTo1555(250, 250, 251);
    gfx_palette[FOREGROUND] = gfx_RGBTo1555(20, 22, 26);
    gfx_palette[ACCENT] = gfx_RGBTo1555(44, 88, 176);
}

static void centre(const char *text, int y)
{
    gfx_PrintStringXY(text, (GFX_LCD_WIDTH - (int)gfx_GetStringWidth(text)) / 2, y);
}

int main(void)
{
    gfx_Begin();
    gfx_SetDrawBuffer();
    palette();
    gfx_FillScreen(BACKGROUND);
    gfx_SetTextTransparentColor(3);
    gfx_SetTextBGColor(3);
    gfx_SetTextFGColor(ACCENT);
    gfx_SetTextScale(3, 3);
    centre("Flight Demo", 80);
    gfx_SetTextFGColor(FOREGROUND);
    gfx_SetTextScale(1, 1);
    centre("built on CEagle Aerie with Flight", 120);
    gfx_SetColor(ACCENT);
    gfx_HorizLine(60, 108, GFX_LCD_WIDTH - 120);
    gfx_SwapDraw();
    while (!os_GetCSC()) {}
    gfx_End();
    return 0;
}
