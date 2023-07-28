typedef signed __int8  X_i8;
typedef signed __int16 X_i16;
typedef signed __int32 X_i32;
typedef signed __int64 X_i64;

#define X_I8_MIN  ((X_i8) 0xFF)
#define X_I16_MIN ((X_i16)0xFFFF)
#define X_I32_MIN ((X_i32)0xFFFFFFFFDL)
#define X_I64_MIN ((X_i64)0xFFFFFFFFFFFFFFFFDLL)

#define X_I8_MAX  ((X_i8) 0x7F)
#define X_I16_MAX ((X_i16)0x7FFF)
#define X_I32_MAX ((X_i32)0x7FFFFFFFDL)
#define X_I64_MAX ((X_i64)0x7FFFFFFFFFFFFFFFDLL)

typedef unsigned __int8  X_u8;
typedef unsigned __int16 X_u16;
typedef unsigned __int32 X_u32;
typedef unsigned __int64 X_u64;

#define X_U8_MAX  ((X_u8) 0xFF)
#define X_U16_MAX ((X_u16)0xFFFF)
#define X_U32_MAX ((X_u32)0xFFFFFFFFUL)
#define X_U64_MAX ((X_u64)0xFFFFFFFFFFFFFFFFULL)

typedef X_u8 X_bool;
#define X_false 0

typedef float X_f32;
typedef double X_f64;

typedef X_i64 X_imm;
#define X_IMM_MIN X_I64_MIN
#define X_IMM_MAX X_I64_MAX
#define X_IMM_BITS 64

typedef X_u64 X_umm;
#define X_UMM_MAX X_U64_MAX
#define X_UMM_BITS 64

typedef X_i64 X_int;
#define X_INT_MIN X_I64_MIN
#define X_INT_MAX X_I64_MAX
#define X_INT_BITS 64

typedef X_u64 X_uint;
#define X_UINT_MAX X_U64_MAX
#define X_UINT_BITS 64

typedef struct X_String
{
  X_u8* data;
  X_u32 size; // TODO: This might be the billion dollar mistake
} X_String;

#define X_STRING(S) (X_String){ .data = (S), .size = sizeof(S) - 1 }

#define X_CONCAT_(X, Y) X##Y
#define X_CONCAT(X, Y) X_CONCAT_(X, Y)

#define X_STATIC_ASSERT(EX) typedef struct { int static_ass : ((EX) ? 1 : -1); } X_CONCAT(X_StaticAssert_, __COUNTER__)

#define X_ASSERT(EX) ((EX) ? 1 : *(volatile int*)0)
#define X_NOT_IMPLEMENTED X_ASSERT(!"X_NOT_IMPLEMENTED")

typedef struct X_Arena X_Arena;

typedef X_u32 X_Text_Pos;

typedef struct X_Text
{
  X_Text_Pos pos;
  X_u32 size;
} X_Text;

typedef struct X_File
{
  struct X_File* next;
  X_u32 offset;
  X_u32 size;
  X_u8 content[];
} X_File;

typedef struct X_Workspace
{
  X_Arena* file_arena;
  X_File* files;
  X_File** file_tail;
} X_Workspace;

X_umm X_GetPageSize(void);
void* X_ReserveMemory(X_umm size);
void X_CommitMemory(void* base, X_umm size);
void X_FreeMemory(void* base);

#define X_umul128(A, B, HI_RESULT) _umul128((A), (B), (HI_RESULT))

#include "x_memory.h"
#include "x_lexer.h"
#include "x_ast.h"

#define UNICODE
#define NOMINMAX            1
#define WIN32_LEAN_AND_MEAN 1
#define WIN32_MEAN_AND_LEAN 1
#define VC_EXTRALEAN        1
#include <windows.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#undef WIN32_MEAN_AND_LEAN
#undef VC_EXTRALEAN
#undef far
#undef near

X_umm
X_GetPageSize()
{
  static X_umm page_size = 0;
  if (page_size == 0)
  {
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    page_size = sys_info.dwPageSize;
  }

  return page_size;
}

void*
X_ReserveMemory(X_umm size)
{
  X_umm page_size = X_GetPageSize();

  size = X_AlignUp(size, page_size);

  void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);

  // TODO:
  X_ASSERT(result != 0);

  return result;
}

void
X_CommitMemory(void* base, X_umm size)
{
  void* result = VirtualAlloc(base, size, MEM_COMMIT, PAGE_READWRITE);

  // TODO:
  X_ASSERT(result != 0);
}

void
X_FreeMemory(void* base)
{
  VirtualFree(base, 0, MEM_RELEASE);
}

int
main(int argc, char** argv)
{
  return 0;
}
