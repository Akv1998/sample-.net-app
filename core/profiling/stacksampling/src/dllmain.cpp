// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "ClassFactory.h"
#include "SampleProfiler.h"

BOOL STDMETHODCALLTYPE DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

void PrintGuid(REFGUID guid)
{
    printf("{%8.8lu-%4.4u-%4.4u-%2.2u%2.2u-%2.2u%2.2u%2.2u%2.2u%2.2u%2.2u}",
           guid.Data1,
           guid.Data2,
           guid.Data3,
           guid.Data4[0],
           guid.Data4[1],
           guid.Data4[2],
           guid.Data4[3],
           guid.Data4[4],
           guid.Data4[5],
           guid.Data4[6],
           guid.Data4[7]);
}

extern "C" HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    // {cf0d821e-299b-5307-a3d8-b283c03916dd}
    const GUID CLSID_CorProfiler = { 0xcf0d821e, 0x299b, 0x5307, { 0xa3, 0xd8, 0xb2, 0x83, 0xc0, 0x39, 0x16, 0xdd } };

    if (ppv == nullptr || rclsid != CLSID_CorProfiler)
    {
        return E_FAIL;
    }

    auto factory = new ClassFactory<SampleProfiler>;
    if (factory == nullptr)
    {
        return E_FAIL;
    }

    return factory->QueryInterface(riid, ppv);
}

extern "C" HRESULT STDMETHODCALLTYPE DllCanUnloadNow()
{
    return S_OK;
}