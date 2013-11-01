#ifndef Macros_h__
#define Macros_h__
#include <windows.h>

#define DEBUG_PRINT(msg) OutputDebugString(msg);
#define CHECKFAIL(cond, msg) if (!cond) { DEBUG_PRINT(msg) return 1; }
#define CHECKPOINTER(ptr, msg) if (ptr == nullptr) { DEBUG_PRINT(msg) return 1; }

#endif // Macros_h__
