#include <Uefi.h>

#include <Library/ConsoleLib/ConsoleLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

//
// SIMPLE_TEXT_INPUT_EX_PROTOCOL
//



//
// SIMPLE_TEXT_INPUT_PROTOCOL
//
void WaitForKey(UINTN *Event)
{
    gST->BootServices->WaitForEvent(1, &gST->ConIn->WaitForKey, Event);
}

EFI_STATUS ReadKeyStroke(OUT EFI_INPUT_KEY *Key)
{
    return gST->ConIn->ReadKeyStroke(gST->ConIn, Key);
}

//
// SIMPLE_TEXT_OUTPUT_PROTOCOL
//
EFI_STATUS QueryMode(UINTN ModeNumber, UINTN *Columns, UINTN *Rows)
{
    return gST->ConOut->QueryMode(gST->ConOut, ModeNumber, Columns, Rows);
}

EFI_STATUS SetMode(UINTN ModeNumber)
{
    return gST->ConOut->SetMode(gST->ConOut, ModeNumber);
}

void ClearScreen(void)
{
    gST->ConOut->ClearScreen(gST->ConOut);
}

void SetColor(UINTN Color)
{
    gST->ConOut->SetAttribute(gST->ConOut, Color);
}

void ResetColor(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY);
}

void SetCursorPosition(UINTN Col, UINTN Row)
{
    gST->ConOut->SetCursorPosition(gST->ConOut, Col, Row);
}

void EnableCursor(BOOLEAN Visible)
{
    gST->ConOut->EnableCursor(gST->ConOut, Visible);
}

INT32 GetMaxMode(void)
{
    return gST->ConOut->Mode->MaxMode;
}

INT32 GetMode(void)
{
    return gST->ConOut->Mode->Mode;
}

INT32 GetAttribute(void)
{
    return gST->ConOut->Mode->Attribute;
}

INT32 GetCursorColumn(void)
{
    return gST->ConOut->Mode->CursorColumn;
}

INT32 GetCursorRow(void)
{
    return gST->ConOut->Mode->CursorRow;
}

BOOLEAN GetCursorVisible(void)
{
    return gST->ConOut->Mode->CursorVisible;
}

//
// CUSTOM
//
void Sleep(UINTN DurationMS)
{
    gBS->Stall(DurationMS * 1000);
}


static void PrintInternal(CHAR16 *String, VA_LIST Args, CHAR16 *Buffer, UINTN BufferSize)
{
    UnicodeVSPrint(
        Buffer,
        BufferSize,
        String,
        Args
    );
}

void PrintColored(UINTN Attribute, CHAR16 *String, ...)
{
    CHAR16 Buffer[256];
    VA_LIST Args;

    VA_START(Args, String);
    PrintInternal(String, Args, Buffer, sizeof(CHAR16) * 256);
    VA_END(Args);

    SetColor(Attribute);
    Print(L"%s", Buffer);
}

void PrintColoredClean(UINTN Attribute, CHAR16 *String, ...)
{
    CHAR16 Buffer[256];
    VA_LIST Args;

    
    //Print(L"\n\n\nPrintColored(): StrLen(Buffer): %u\n", StrLen(Buffer));
    //Print(L"PrintColored(): StrLen(String): %u\n", StrLen(String));
    VA_START(Args, String);
    PrintInternal(String, Args, Buffer, sizeof(CHAR16) * 256);
    VA_END(Args);
    //Print(L"\nPrintColored(): StrLen(Buffer): %u\n", StrLen(Buffer));
    //Print(L"PrintColored(): StrLen(String): %u\n", StrLen(String));
    
    UINTN OldColor = GetAttribute();
    SetColor(Attribute);
    Print(L"%s", Buffer);   
    SetColor(OldColor);
}


void PrintAligned(UINTN Attribute, UINTN Width, UINTN Alignment, CHAR16 *String, ...)
{
    CHAR16 Buffer[256];
    VA_LIST Args;

    VA_START(Args, String);
    //Print(L"PrintAligned(): sizeof(Buffer): %u", sizeof(Buffer));
    PrintInternal(String, Args, Buffer, sizeof(CHAR16) * 256);
    VA_END(Args);

    UINTN Len = StrLen(Buffer);
    UINTN Spaces;
    UINTN i;
    //Print(L"\nPrintAligned(): StrLen(Buffer): %u\n", Len);
    //Print(L"PrintAligned(): Width         : %u\n", Width);
    if (Len < Width)
    {
        if (Alignment == ALIGN_RIGHT)
        {
            Spaces = Width - Len;
            for (i = 0; i < Spaces; i++)
            {
                Print(L" ");
            }
        }
        else if (Alignment == ALIGN_CENTER)
        {
            Spaces = (Width - Len) / 2;
            for (i = 0; i < Spaces; i++)
            {
                Print(L" ");
            }
        }
    }

    UINTN OldColor = GetAttribute();
    SetColor(Attribute);
    Print(L"%s", Buffer);
    SetColor(OldColor);

    if (Len < Width)
    {
        if (Alignment == ALIGN_LEFT)
        {
            Spaces = Width - Len;
            for (i = 0; i < Spaces; i++)
            {
                Print(L" ");
            }
        }
        else if (Alignment == ALIGN_CENTER)
        {
            Spaces = (Width - Len) / 2 + ((Width - Len) % 2);
            for (i = 0; i < Spaces; i++)
            {
                Print(L" ");
            }
        }
    }
}

void PrintError(CHAR16 *String)
{
    PrintColoredClean(EFI_BACKGROUND_RED | EFI_WHITE, String);
}

void PrintMultistringAnim(UINTN Arguments, UINTN StartX, UINTN StartY, UINTN Delay, UINTN Length, CHAR16 *Multistring[])
{
    SetColor(Arguments);
    for (UINTN i = 0; i < Length; i++)
    {
        SetCursorPosition(StartX, StartY + i);
        Print(L"%s", Multistring[i]);
        Sleep(Delay);
    }
}