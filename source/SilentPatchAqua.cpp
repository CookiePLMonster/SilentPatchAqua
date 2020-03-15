#include "Utils/MemoryMgr.h"

void OnInitializeHook()
{
	using namespace Memory::VP;

	// If it's not 1.18, bail out
	// Both Steam and GOG versions are 1.18 so it -should- be OK
	if ( !MemEquals( 0x42A7A0, { 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50 } ) )
	{
#ifndef _DEBUG
		MessageBoxW( nullptr, L"You are using an executable version not supported by SilentPatch!\n\n"
			L"Only version 1.18 is supported - that is, Steam and GOG releases. Old retail releases are likely unsupported, "
			L"and possibly never will.",
			L"SilentPatch",
			MB_OK | MB_ICONWARNING );
#endif
		return;
	}

	// Fix DirectInput buffer overflow being treated as failure
	// This is fixed in AquaNox 2
	// jne -> jl
	Patch<uint8_t>( 0x51CACA, 0x7C ); // Mouse
	Patch<uint8_t>( 0x51B790, 0x7C ); // Keyboard
}
