#include "Utils/MemoryMgr.h"
#include "Utils/Patterns.h"

void OnInitializeHook()
{
	using namespace Memory::VP;
	using namespace hook;

	// Fix DirectInput buffer overflow being treated as failure
	// This is fixed in AquaNox 2
	// jne -> jl
	pattern( "6A 14 50 FF 51 28 85 C0 75" ).count(3).for_each_result([] ( pattern_match match ) { // This pattern will fail if eg. GOG.com applies this patch
		Patch<uint8_t>( match.get<void>( 8 ), 0x7C );											// in executable directly, but it's fine as it'll just never execute this lambda
	} );
}
