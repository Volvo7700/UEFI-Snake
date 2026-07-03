#include <Uefi.h>

#include <Library/ConsoleLib/ConsoleLib.h>
#include <Library/SnakeLib/SnakeLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

void TextModeSelector()
{
    Print(L"\n\nQuerying Text Modes...\n");
    
    PrintColored(EFI_RED, L"\n=== Available Text Modes: ===\n");
    PrintColored(EFI_YELLOW, L" Mode   Wdh    Hgt\n");
    
    UINTN CurrentMode = GetMode();
    UINTN TextCols;
    UINTN TextRows;
    UINTN Color1;
    UINTN Color2;
    for (UINTN i = 0; i < GetMaxMode(); i++)
    {
        QueryMode(i, &TextCols, &TextRows);
        
        if (i == CurrentMode)
        {
            Color1 = EFI_YELLOW;
            Color2 = EFI_WHITE;
            PrintColored(Color1, L" * ");
        }
        else
        {
            Color1 = EFI_WHITE;
            Color2 = EFI_LIGHTGRAY;
            PrintColored(Color1, L"   ");
        }
        
        PrintAligned(Color1, 2, ALIGN_RIGHT, L"%u", i);
        PrintColored(EFI_DARKGRAY, L"  ");
        PrintAligned(Color2, 4, ALIGN_RIGHT, L"%u", TextCols);
        PrintColored(EFI_DARKGRAY, L" x ");
        PrintAligned(Color2, 4, ALIGN_RIGHT, L"%u", TextRows);
        Print(L"\n");
    }
    PrintColored(EFI_CYAN, L"\nSelection: ");
    EnableCursor(TRUE);
    
    UINTN EventInd;
    EFI_INPUT_KEY Key;
    WaitForKey(&EventInd);
    ReadKeyStroke(&Key);

    EnableCursor(FALSE);
    
    BOOLEAN ModeFound = FALSE;
    for (UINTN i = 0; i < GetMaxMode(); i++)
    {
        if (i == Key.UnicodeChar - L'0')
        {
            ModeFound = TRUE;
            EFI_STATUS Status = SetMode(i);
            switch (Status)
            {
                case EFI_DEVICE_ERROR:
                    Print(L"Device error\n");
                    break;
                case EFI_UNSUPPORTED:
                    Print(L"Invalid mode\n");
                    break;
            default:
                Print(L"Mode changed to %u\n", i);
                break;
            }
        }
    }
    if (!ModeFound)
    {
        Print(L"Mode not found");
    }
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    Print(L"\n\nHello from Clang + EDK II + QEMU!\n");
    
    PrintColored(EFI_LIGHTRED, L"\nUV7");
    PrintColored(EFI_RED, L" UEFI Snake Subsystem\n");
    
    PrintColored(EFI_BACKGROUND_BLUE | EFI_WHITE, L"\nWork in Progress... First \"Concept\"\n");


    SnakeInit();
    //TextModeSelector();

    Sleep(2000);
    
    ResetColor();
    Print(L"\n\nPress any key to restart...\n");
    EnableCursor(TRUE);
    UINTN Event;
    WaitForKey(&Event);
#if defined(DEBUG)
    // If running in debug mode, use the EFI shut down call to close QEMU
    Print(L"Shutting down...");
    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
#endif

    return EFI_SUCCESS;
}