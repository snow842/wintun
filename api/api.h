/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (C) 2018-2020 WireGuard LLC. All Rights Reserved.
 */

#pragma once

#include <Windows.h>

extern HINSTANCE ResourceModule;

_Check_return_
HANDLE
TakeNameMutex(_In_z_ LPCWSTR Pool);

void
ReleaseNameMutex(_In_ HANDLE Mutex);

void
NamespaceInit();

void
NamespaceCleanup();

_Return_type_success_(return ==
                             0) extern DWORD(WINAPI *NciSetConnectionName)(_In_ LPCGUID Guid, _In_z_ LPCWSTR NewName);

_Return_type_success_(return == 0) extern DWORD(WINAPI *NciGetConnectionName)(
    _In_ LPCGUID Guid,
    _Out_z_bytecap_(InDestNameBytes) LPWSTR Name,
    _In_ DWORD InDestNameBytes,
    _Out_opt_ DWORD *OutDestNameBytes);

void
NciInit();

void
NciCleanup();

#define MAX_POOL 256
#define MAX_INSTANCE_ID MAX_PATH        /* TODO: Is MAX_PATH always enough? */

typedef struct _WINTUN_ADAPTER
{
    GUID CfgInstanceID;
    WCHAR DevInstanceID[MAX_INSTANCE_ID];
    DWORD LuidIndex;
    DWORD IfType;
    WCHAR Pool[MAX_POOL];
} WINTUN_ADAPTER;

_Return_type_success_(return == 0) DWORD WINAPI
    WintunGetAdapter(_In_z_count_c_(MAX_POOL) LPCWSTR Pool, _In_z_ LPCWSTR IfName, _Out_ WINTUN_ADAPTER **Adapter);

VOID WINAPI
WintunFreeAdapter(_In_ WINTUN_ADAPTER *Adapter);
