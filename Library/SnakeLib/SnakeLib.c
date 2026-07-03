#include <Uefi.h>

#include <Library/ConsoleLib/ConsoleLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

#define SNAKE_MAX_LEN 2340
#define PRE_TERMINAL_W 80
#define PRE_TERMINAL_H 32
#define PRE_SNAKE_LEN 5

#define ANIM_DELAY 4000
#define ANIM_SPEED 100
#define ANIM_SUB { \
    L"██    ██  ██    ██  ████████", \
    L"██    ██   ██  ██        ██ ", \
    L"██    ██    ████        ██  ", \
    L" ██████      ██        ██   " \
}
#define ANIM_MAIN { \
    L" ████████     ██      ██        ██        ██     ███    ██████████", \
    L"██████████    ███     ██        ██        ██    ███     ██████████", \
    L"██       █    ████    ██       ████       ██   ███      ██        ", \
    L"██            █████   ██       ████       ██  ███       ██        ", \
    L"█████████     ██ ███  ██      ██  ██      ██████        ██████████", \
    L" █████████    ██  ███ ██      ██  ██      ██████        ██████████", \
    L"        ██    ██   █████     ████████     ██  ███       ██        ", \
    L"█       ██    ██    ████     ████████     ██   ███      ██        ", \
    L"██████████    ██     ███    ██      ██    ██    ███     ██████████", \
    L" ████████     ██      ██    ██      ██    ██     ███    ██████████" \
};
#define ANIM_SUB_W 28
#define ANIM_MAIN_W 66
#define ANIM_H 15
#define TEXT L" UEFI Edition "

UINTN W = PRE_TERMINAL_W;   // Terminal Width
UINTN H = PRE_TERMINAL_H;   // Terminal Height

UINTN X[SNAKE_MAX_LEN];     // Snake Coordinates X
UINTN Y[SNAKE_MAX_LEN];     // Snake Coordinates Y

UINTN FX = 0;               // Fruit Coordinate X
UINTN FY = 0;               // Fruit Coordinate Y

UINTN P = PRE_SNAKE_LEN;    // Snake Parts (Length)

UINT8 D = 0;                // Snake Direction

//UINTN CX =                  // Cursor Coordinate X
//UINTN CY =                  // Cursor Coordinate Y

UINTN S = 75;               // Speed (Delay)

BOOLEAN GameRunning = FALSE;
BOOLEAN GameOver = FALSE;

void Animation()
{
    UINTN SubX = (W - ANIM_SUB_W) / 2;
    UINTN MainX = (W - ANIM_MAIN_W) / 2;

    UINTN AnimH = ANIM_H + 2;
    UINTN SubY = (H - AnimH) / 2;
    UINTN MainY = SubY + 5;
    UINTN TextY = MainY + 11;

    CHAR16 *AnimSub[] = ANIM_SUB;
    CHAR16 *AnimMain[] = ANIM_MAIN;

    SetColor(EFI_BACKGROUND_LIGHTGRAY | EFI_WHITE);
    SetCursorPosition(0, TextY);
    PrintAligned(EFI_BACKGROUND_BLACK | EFI_WHITE, W, ALIGN_CENTER, TEXT);

    UINT8 i = 0;
    while (TRUE)
    {
        switch (i)
        {
            case 0:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_RED, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTRED, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 1:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_RED, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTRED, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 2:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_BROWN, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_YELLOW, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 3:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_GREEN, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTGREEN, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 4:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_CYAN, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTCYAN, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 5:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_BLUE, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTBLUE, MainX, MainY, ANIM_SPEED, 10, AnimMain);    
                break;
            case 6:
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_MAGENTA, SubX, SubY, ANIM_SPEED, 4, AnimSub);
                PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTMAGENTA, MainX, MainY, ANIM_SPEED, 10, AnimMain);
                i = 0;
                break;
        }
        Sleep(ANIM_DELAY);

        i++;
    }

    PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_RED, SubX, 5, ANIM_SPEED, 4, AnimSub);
    PrintMultistringAnim(EFI_BACKGROUND_BLACK | EFI_LIGHTRED, MainX, 10, ANIM_SPEED, 10, AnimMain);
}

void SnakeInit(void)
{
    UINTN Mode = GetMode();
    EFI_STATUS Status = QueryMode(Mode, &W, &H);
    if (Status != EFI_SUCCESS)
    {
        PrintError(L"Querying Mode Failed");
        return;
    }

    Animation();
}