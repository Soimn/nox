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
#define X_true 1
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

X_bool
X_String_Match(X_String s0, X_String s1)
{
  X_bool result = (s0.size == s1.size);

  for (X_uint i = 0; i < s0.size && result != X_false; ++i) result = (s0.data[i] == s1.data[i]);

  return result;
}

#define X_STATIC_ARRAY_SIZE(A) (sizeof(A)/sizeof(0[A]))

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
#include "x_int.h"
#include "x_float.h"
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

#include <stdio.h>
#include <string.h>

int
main(int argc, char** argv)
{
  if (argc == 2 && strcmp(argv[1], "test") == 0)
  {
    { /// X_i128
      X_i128 a                  = {0};
      X_I128_Status_Flag status = 0;

      X_u64 x = 63792321;
      a = X_I128_AddU64(a, x, &status);
      X_ASSERT(a.hi == 0);
      X_ASSERT(a.lo == x);
      X_ASSERT(status == 0);

      a = X_I128_MulU64(a, 10, &status);
      X_ASSERT(a.hi == 0);
      X_ASSERT(a.lo == x*10);
      X_ASSERT(status == 0);

      a = X_I128_Neg(a);
      X_ASSERT(a.hi == ~0ULL);
      X_ASSERT(a.lo == (X_u64)-(X_i64)(x*10));

      a = X_I128_Mul(a, (X_i128){ .hi = ~0ULL, .lo = ~0ULL }, &status);
      X_ASSERT(a.hi == 0);
      X_ASSERT(a.lo == x*10);
      X_ASSERT(status == 0);
    }

    { /// X_Lexer
      X_Lexer lexer = X_Lexer_Init(X_STRING("+\f/* Thi is\r\n a //\t\t /* deep \v*/ co\fmment \r\n*/,/%->-// ---\r\n>---=+=\r\n\t!~=\r\n\r\n \r\n"
                                            "001023456789 0xA11BAdF00dFF00FF4242694200000001zadidentifier\"\\\"\\tzad\"proc"
                                           ), 0, 0, 1);

      X_Token match_tokens[] = {
        [0]  = { .kind = X_Token_Plus,        .text.pos =   0, .text.size =  1, .offset_to_line =  0, .line = 1 },
        [1]  = { .kind = X_Token_Comma,       .text.pos =  46, .text.size =  1, .offset_to_line = 44, .line = 3 },
        [2]  = { .kind = X_Token_Slash,       .text.pos =  47, .text.size =  1, .offset_to_line = 44, .line = 3 },
        [3]  = { .kind = X_Token_Rem,         .text.pos =  48, .text.size =  1, .offset_to_line = 44, .line = 3 },
        [4]  = { .kind = X_Token_Arrow,       .text.pos =  49, .text.size =  2, .offset_to_line = 44, .line = 3 },
        [5]  = { .kind = X_Token_Minus,       .text.pos =  51, .text.size =  1, .offset_to_line = 44, .line = 3 },
        [6]  = { .kind = X_Token_Greater,     .text.pos =  60, .text.size =  1, .offset_to_line = 60, .line = 4 },
        [7]  = { .kind = X_Token_TripleMinus, .text.pos =  61, .text.size =  3, .offset_to_line = 60, .line = 4 },
        [8]  = { .kind = X_Token_Equals,      .text.pos =  64, .text.size =  1, .offset_to_line = 60, .line = 4 },
        [9]  = { .kind = X_Token_PlusEQ,      .text.pos =  65, .text.size =  2, .offset_to_line = 60, .line = 4 },
        [10] = { .kind = X_Token_Not,         .text.pos =  70, .text.size =  1, .offset_to_line = 69, .line = 5 },
        [11] = { .kind = X_Token_BitXorEQ,    .text.pos =  71, .text.size =  2, .offset_to_line = 69, .line = 5 },
        [12] = { .kind = X_Token_Int,         .text.pos =  80, .text.size = 12, .offset_to_line = 80, .line = 8, .integer = (X_i128){ .hi = 0, .lo = 1023456789 } },
        [13] = { .kind = X_Token_Int,         .text.pos =  93, .text.size = 34, .offset_to_line = 80, .line = 8, .integer = (X_i128){ .hi = 0xA11BAdF00dFF00FFULL, .lo = 0x4242694200000001ULL } },
        [14] = { .kind = X_Token_Identifier,  .text.pos = 127, .text.size = 13, .offset_to_line = 80, .line = 8, .string = X_STRING("zadidentifier") },
        [15] = { .kind = X_Token_String,      .text.pos = 140, .text.size =  9, .offset_to_line = 80, .line = 8, .string = X_STRING("\\\"\\tzad") },
        [16] = { .kind = X_Token_Proc,        .text.pos = 149, .text.size =  4, .offset_to_line = 80, .line = 8, .string = X_STRING("proc") },
        [17] = { .kind = X_Token_EndOfFile,   .text.pos = 153, .text.size =  0, .offset_to_line = 80, .line = 8 },
        [18] = { .kind = X_Token_EndOfFile,   .text.pos = 153, .text.size =  0, .offset_to_line = 80, .line = 8 },
        [19] = { .kind = X_Token_EndOfFile,   .text.pos = 153, .text.size =  0, .offset_to_line = 80, .line = 8 },
      };

      for (X_uint i = 0; i < X_STATIC_ARRAY_SIZE(match_tokens); ++i)
      {
        X_Token t  = X_Lexer_NextToken(&lexer);
        X_Token mt = match_tokens[i];

        if (t.kind != mt.kind || t.text.pos != mt.text.pos || t.text.size != mt.text.size || t.offset_to_line != mt.offset_to_line || t.line != mt.line ||
            (t.kind == X_Token_Int        && (t.integer.lo != mt.integer.lo || t.integer.hi != mt.integer.hi) ||
             t.kind == X_Token_Identifier && !X_String_Match(t.string, mt.string)                             ||
             t.kind == X_Token_String     && !X_String_Match(t.string, mt.string)))
        {
          printf("TOKEN MISMATCH (%llu)\n", i);
          break;
        }
      }
    }

    printf("Done");
  }

  return 0;
}
