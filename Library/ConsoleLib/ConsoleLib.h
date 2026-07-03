#pragma once

#include <Uefi.h>

#define ALIGN_RIGHT 0
#define ALIGN_LEFT 1
#define ALIGN_CENTER 2

//
// SIMPLE_TEXT_INPUT_EX_PROTOCOL
//
BOOLEAN ResetInputEx(void);
EFI_STATUS ReadKeyStrokeEx(OUT EFI_KEY_DATA *KeyData);
EFI_STATUS SetStatus(EFI_KEY_TOGGLE_STATE *KeyToggleState);
BOOLEAN RegisterKeyNotify(EFI_KEY_DATA *KeyData, EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction, OUT VOID **NotifyHandle);
BOOLEAN UnregisterKeyNotify(VOID **NotifyHandle);

//
// SIMPLE_TEXT_INPUT_PROTOCOL
//
void ResetInput();
EFI_STATUS ReadKeyStroke(OUT EFI_INPUT_KEY *Key);
void WaitForKey(UINTN *Event);

//
// SIMPLE_TEXT_OUTPUT_PROTOCOL
//
void ResetOutput(void);
void OutputString(CHAR16 *String);
BOOLEAN TestString(CHAR16 *String);
EFI_STATUS QueryMode(UINTN ModeNumber, UINTN *Columns, UINTN *Rows);
EFI_STATUS SetMode(UINTN ModeNumber);
void ClearScreen(void);
void SetColor(UINTN Color);
void ResetColor(void);
void SetCursorPosition(UINTN Col, UINTN Row);
void EnableCursor(BOOLEAN Visible);

INT32 GetMaxMode(void);
INT32 GetMode(void);
INT32 GetAttribute(void);
INT32 GetCursorColumn(void);
INT32 GetCursorRow(void);
BOOLEAN GetCursorVisible(void);

//
// CUSTOM
//
void Sleep(UINTN DurationMS);
BOOLEAN ReadLine(OUT CHAR16 *String, UINTN Length);
void PrintColored(UINTN Arguments, CHAR16 *String, ...);
void PrintAligned(UINTN Arguments, UINTN Width, UINTN Alignment, CHAR16 *String, ...);