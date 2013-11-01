#ifndef Macros_h__
#define Macros_h__
#include <windows.h>

#define _DEBUG_MODE 1
#define DEBUG_PRINT(msg) if (_DEBUG_MODE) OutputDebugString(msg);
#define CHECKFAIL(cond, msg) if (!cond) { DEBUG_PRINT(msg) return 1; }
#define CHECKPOINTER(ptr, msg) if (ptr == nullptr) { DEBUG_PRINT(msg) return 1; }

#endif // Macros_h__
