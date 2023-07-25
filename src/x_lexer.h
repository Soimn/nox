#define X_TOKEN_KIND__BLOCK(N) ((N) << 4)

#define X_TOKEN_KIND__BASS_TO_B(K) ((K) & 0x7F)
#define X_TOKEN_KIND__B_TO_BASS(K) ((K) | 0x80)

typedef enum X_Token_Kind
{
  /// BLOCK 0
  X_Token_Invalid = 0,
  X_Token_EndOfFile,
  X_Token_OpenParen,                           // (
  X_Token_CloseParen,                          // )
  X_Token_OpenBracket,                         // [
  X_Token_CloseBracket,                        // ]
  X_Token_OpenBrace,                           // {
  X_Token_CloseBrace,                          // }
  X_Token_Period,                              // .
  X_Token_PeriodParen,                         // .(
  X_Token_PeriodBracket,                       // .[
  X_Token_PeriodBrace,                         // .{
  X_Token_Cash,                                // $
  X_Token_Colon,                               // :
  X_Token_Comma,                               // ,
  X_Token_Semicolon,                           // ;
  X_Token__PastLastBlock0,

  /// BLOCK 1
  X_Token__FirstBlock1 = X_TOKEN_KIND__BLOCK(1),
  X_Token_BitNot = X_Token__FirstBlock1,       // ~
  X_Token_Hat,                                 // ^
  X_Token_Arrow,                               // ->
  X_Token_Qmark,                               // ?
  X_Token_TripleMinus,                         // ---
  X_Token_Not,                                 // !
  X_Token_Identifier,
  X_Token_String,
  X_Token_Int,
  X_Token_Float,
  X_Token__PastLastBlock1,

  /// BLOCK 2
  X_Token__FirstMulLevel = X_TOKEN_KIND__BLOCK(2),
  X_Token_Star = X_Token__FirstMulLevel,         // *
  X_Token_Slash,                               // /
  X_Token_Rem,                                 // %
  X_Token_BitAnd,                              // &
  X_Token_BitShr,                              // >>
  X_Token_BitSar,                              // >>>
  X_Token_BitShl,                              // <<
  X_Token__PastLastMulLevel,

  /// BLOCK 3
  X_Token__FirstAddLevel = X_TOKEN_KIND__BLOCK(3),
  X_Token_Plus = X_Token__FirstAddLevel,         // +
  X_Token_Minus,                               // -
  X_Token_BitOr,                               // |
  X_Token_BitXor,                              // ~
  X_Token__PastLastAddLevel,

  /// BLOCK 4
  X_Token__FirstCmpLevel = X_TOKEN_KIND__BLOCK(4),
  X_Token_EqualsEQ = X_Token__FirstCmpLevel,     // ==
  X_Token_NotEQ,                               // !=
  X_Token_Less,                                // <
  X_Token_LessEQ,                              // <=
  X_Token_Greater,                             // >
  X_Token_GreaterEQ,                           // >=
  X_Token__PastLastCmpLevel,

  /// BLOCK 5
  X_Token__FirstAndLevel = X_TOKEN_KIND__BLOCK(5),
  X_Token_And = X_Token__FirstAndLevel,          // &&
  X_Token__PastLastAndLevel,

  /// BLOCK 6
  X_Token__FirstOrLevel = X_TOKEN_KIND__BLOCK(6),
  X_Token_Or = X_Token__FirstOrLevel,            // ||
  X_Token__PastLastOrLevel,

  /// BLOCK 7
  X_Token__FirstKeyword = X_TOKEN_KIND__BLOCK(7),
  X_Token_If = X_Token__FirstKeyword,
  X_Token_Else,
  X_Token_Return,
  X_Token_Continue,
  X_Token_Break,
  X_Token_True,
  X_Token_False,
  X_Token_Proc,
  X_Token_Struct,
  X_Token_Asm,
  X_Token__PastLastKeyword,

  /// BLOCK 8

  /// BLOCK 9
  X_Token__FirstAssignment,
  X_Token_Equals = X_Token__FirstAssignment,     // =

  /// BLOCK 10
  X_Token__FirstMulLevelAssign = X_TOKEN_KIND__BLOCK(8 + 2),
  X_Token_StarEQ = X_Token__FirstMulLevelAssign, // *=
  X_Token_SlashEQ,                             // /=
  X_Token_RemEQ,                               // %=
  X_Token_BitAndEQ,                            // &=
  X_Token_BitShrEQ,                            // >>=
  X_Token_BitSarEQ,                            // >>>=
  X_Token_BitShlEQ,                            // <<=
  X_Token__PastLastMulLevelAssign,

  /// BLOCK 11
  X_Token__FirstAddLevelAssign = X_TOKEN_KIND__BLOCK(8 + 3),
  X_Token_PlusEQ = X_Token__FirstAddLevelAssign, // +=
  X_Token_MinusEQ,                             // -=
  X_Token_BitOrEQ,                             // |=
  X_Token_BitXorEQ,                            // ^=
  X_Token__PastLastAddLevelAssign,

  /// BLOCK 12
  // NOTE: block 12 is not used for assignment (cmp level)

  /// BLOCK 13
  X_Token__FirstAndLevelAssign = X_TOKEN_KIND__BLOCK(8 + 5),
  X_Token_AndEQ = X_Token__FirstAndLevelAssign,  // &&=
  X_Token__PastLastAndLevelAssign,

  /// BLOCK 14
  X_Token__FirstOrLevelAssign = X_TOKEN_KIND__BLOCK(8 + 6),
  X_Token_OrEQ = X_Token__FirstOrLevelAssign,    // ||=
  X_Token__PastLastOrLevelAssign,

  X_Token__PastLastAssignment,

  /// BLOCK 15 -
} X_Token_Kind;

X_STATIC_ASSERT(X_Token__PastLastBlock0         <= X_Token__FirstBlock1);
X_STATIC_ASSERT(X_Token__PastLastBlock1         <= X_Token__FirstMulLevel);
X_STATIC_ASSERT(X_Token__PastLastMulLevel       <= X_Token__FirstAddLevel);
X_STATIC_ASSERT(X_Token__PastLastAddLevel       <= X_Token__FirstCmpLevel);
X_STATIC_ASSERT(X_Token__PastLastCmpLevel       <= X_Token__FirstAndLevel);
X_STATIC_ASSERT(X_Token__PastLastAndLevel       <= X_Token__FirstOrLevel);
X_STATIC_ASSERT(X_Token__PastLastOrLevel        <= X_Token__FirstKeyword);
X_STATIC_ASSERT(X_Token__PastLastKeyword        <= X_Token__FirstAssignment);
X_STATIC_ASSERT(X_Token_Equals < X_Token__FirstMulLevelAssign);
X_STATIC_ASSERT(X_Token__PastLastMulLevelAssign <= X_Token__FirstAddLevelAssign);
X_STATIC_ASSERT(X_Token__PastLastAddLevelAssign <= X_Token__FirstAndLevelAssign);
X_STATIC_ASSERT(X_Token__PastLastAndLevelAssign <= X_Token__FirstOrLevelAssign);

#undef X_TOKEN_KIND__BLOCK

typedef struct X_Token
{
  X_u8 kind;
  X_Text text;
  X_u32 offset_to_line;
  X_u32 line;
} X_Token;

typedef struct X_Lexer
{
  X_u64 cursor; // NOTE: 64 bit to avoid overflow
  X_String input;

  X_Text_Pos init_pos;
  X_u32 offset_to_line;
  X_u32 line;
} X_Lexer;

X_Lexer
X_Lexer_Init(X_String input, X_Text_Pos pos, X_u32 offset_to_line, X_u32 line)
{
  return (X_Lexer){
    .cursor         = 0,
    .input          = input,
    .init_pos       = pos,
    .offset_to_line = offset_to_line,
    .line           = line,
  };
}

X_Token
X_Lexer_NextToken(X_Lexer* lexer)
{
  X_Token token = { .kind = X_Token_Invalid };

  for (;;)
  {
  }

  token.text = (X_Text){
    .pos  = ,
    .size = ,
  };
  return token;
}

#undef X_TOKEN_KIND__B_TO_BASS
#undef X_TOKEN_KIND__BASS_TO_B