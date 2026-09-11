#include <demolib.h>
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

/* Everything below runs through LibLoad, in the library this program depends
 * on. Flight fetched its stub and its header from Roost before the build
 * started; the library itself was never rebuilt here. */
static void digits(char *out, uint24_t value)
{
    uint24_t length = 0;

    do
    {
        out[length++] = (char)('0' + value % 10);
        value /= 10;
    } while (value != 0);

    out[length] = '\0';

    /* Written least significant digit first, so put it the right way round. */
    demolib_reverse(out);
}

int main(void)
{
    char answer[8];

    digits(answer, demolib_gcd(84, 36));

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
    gfx_SetTextFGColor(ACCENT);
    gfx_PrintStringXY("gcd(84, 36) = ", 96, 142);
    gfx_PrintString(answer);
    gfx_SetTextFGColor(FOREGROUND);
    centre("answered by DEMOLIB, fetched not rebuilt", 160);
    gfx_SetColor(ACCENT);
    gfx_HorizLine(60, 108, GFX_LCD_WIDTH - 120);
    gfx_SwapDraw();
    while (!os_GetCSC()) {}
    gfx_End();
    return 0;
}
