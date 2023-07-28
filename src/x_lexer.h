#define X_TOKEN_KIND__BLOCK(N) ((N) << 4)

#define X_TOKEN_KIND__BASS_TO_B(K) ((K) & 0x7F)
#define X_TOKEN_KIND__B_TO_BASS(K) ((K) | 0x80)
#define X_TOKEN_KIND__BASS_BIT_IDX 7

typedef enum X_Token_Kind
{
  /// BLOCK 0
  X_Token_Invalid = 0,
  X_Token_EndOfFile,
  X_Token_OpenParen,                             // (
  X_Token_CloseParen,                            // )
  X_Token_OpenBracket,                           // [
  X_Token_CloseBracket,                          // ]
  X_Token_OpenBrace,                             // {
  X_Token_CloseBrace,                            // }
  X_Token_Cash,                                  // $
  X_Token_Colon,                                 // :
  X_Token_Comma,                                 // ,
  X_Token_Semicolon,                             // ;
  X_Token_Arrow,                                 // ->
  X_Token_Qmark,                                 // ?
  X_Token_TripleMinus,                           // ---
  X_Token_Not,                                   // !
  X_Token__PastLastBlock0,

  /// BLOCK 1
  X_Token__FirstBlock1 = X_TOKEN_KIND__BLOCK(1),
  X_Token_BitNot = X_Token__FirstBlock1,         // ~
  X_Token_Hat,                                   // ^
  X_Token_Period,                                // .
  X_Token_Elipsis,                               // ..
  X_Token_ElipsisLess,                           // ..<
  X_Token_PeriodParen,                           // .(
  X_Token_PeriodBracket,                         // .[
  X_Token_PeriodBrace,                           // .{
  X_Token_Underscore,                            // _
  X_Token_Identifier,
  X_Token_String,
  X_Token_Int,
  X_Token_Float,
  X_Token__PastLastBlock1,

  /// BLOCK 2
  X_Token__FirstMulLevel = X_TOKEN_KIND__BLOCK(2),
  X_Token_Star = X_Token__FirstMulLevel,         // *
  X_Token_Slash,                                 // /
  X_Token_Rem,                                   // %
  X_Token_BitAnd,                                // &
  X_Token_BitShr,                                // >>
  X_Token_BitSar,                                // >>>
  X_Token_BitShl,                                // <<
  X_Token__PastLastMulLevel,

  /// BLOCK 3
  X_Token__FirstAddLevel = X_TOKEN_KIND__BLOCK(3),
  X_Token_Plus = X_Token__FirstAddLevel,         // +
  X_Token_Minus,                                 // -
  X_Token_BitOr,                                 // |
  X_Token_BitXor,                                // ~
  X_Token__PastLastAddLevel,

  /// BLOCK 4
  X_Token__FirstCmpLevel = X_TOKEN_KIND__BLOCK(4),
  X_Token_EqualsEQ = X_Token__FirstCmpLevel,     // ==
  X_Token_NotEQ,                                 // !=
  X_Token_Less,                                  // <
  X_Token_LessEQ,                                // <=
  X_Token_Greater,                               // >
  X_Token_GreaterEQ,                             // >=
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
  X_Token_SlashEQ,                               // /=
  X_Token_RemEQ,                                 // %=
  X_Token_BitAndEQ,                              // &=
  X_Token_BitShrEQ,                              // >>=
  X_Token_BitSarEQ,                              // >>>=
  X_Token_BitShlEQ,                              // <<=
  X_Token__PastLastMulLevelAssign,

  /// BLOCK 11
  X_Token__FirstAddLevelAssign = X_TOKEN_KIND__BLOCK(8 + 3),
  X_Token_PlusEQ = X_Token__FirstAddLevelAssign, // +=
  X_Token_MinusEQ,                               // -=
  X_Token_BitOrEQ,                               // |=
  X_Token_BitXorEQ,                              // ^=
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
  X_u32 init_offset_to_line;
  X_u32 line_cursor;
  X_u32 line;
} X_Lexer;

X_Lexer
X_Lexer_Init(X_String input, X_Text_Pos pos, X_u32 offset_to_line, X_u32 line)
{
  return (X_Lexer){
    .cursor              = 0,
    .input               = input,
    .init_pos            = pos,
    .init_offset_to_line = offset_to_line,
    .line_cursor         = 0,
    .line                = line,
  };
}

X_bool
X_Lexer__IsAlpha(X_u8 c)
{
  return ((X_u8)((c&0xDF) - 'A') <= (X_u8)('Z' - 'A'));
}

X_bool
X_Lexer__IsDigit(X_u8 c)
{
  return ((X_u8)(c - '0') < 10);
}

X_bool
X_Lexer__IsHexAlphaDigit(X_u8 c)
{
  return ((X_u8)((c&0xDF) - 'A') <= (X_u8)('F' - 'A'));
}

X_Token
X_Lexer_NextToken(X_Lexer* lexer)
{
  X_Token token = { .kind = X_Token_Invalid };

  for (;;)
  {
    X_u8 c  = (lexer->cursor   < lexer->input.size ? lexer->input.data[lexer->cursor]   : 0);
    X_u8 c1 = (lexer->cursor+1 < lexer->input.size ? lexer->input.data[lexer->cursor+1] : 0);
    if (c == '\n')
    {
      lexer->cursor += 1;

      lexer->line_cursor = (X_u32)lexer->cursor;
      lexer->line       += 1;
    }
    else if (c == ' '  || c == '\t' ||
             c == '\v' || c == '\f' ||
             c == '\r')
    {
      lexer->cursor += 1;
    }
    else if (c == '/' && c1 == '/')
    {
      lexer->cursor += 2;
      while (lexer->cursor < lexer->input.size && *lexer->input.data != '\n') lexer->cursor += 1;
    }
    else if (c == '/' && c1 == '*')
    {
      lexer->cursor += 2;
      for (X_uint nesting = 1; nesting != 0;)
      {
        if (lexer->cursor + 1 >= lexer->input.size)
        {
          //// ERROR: Unterminated block comment
          X_NOT_IMPLEMENTED;
          break;
        }
        else
        {
          c  = lexer->input.data[lexer->cursor];
          lexer->cursor += 1;
          c1 = lexer->input.data[lexer->cursor];
          if      (c == '/' && c1 == '*') lexer->cursor += 1, nesting += 1;
          else if (c == '*' && c1 == '/') lexer->cursor += 1, nesting -= 1;
          else if (c == '\n')
          {
            lexer->line_cursor = (X_u32)lexer->cursor;
            lexer->line       += 1;
          }
        }
      }
    }
    else break;
  }

  X_ASSERT(lexer->cursor <= X_U32_MAX - lexer->init_pos);
  token.text.pos       = (X_u32)(lexer->init_pos + lexer->cursor);
  // NOTE: token.text.size is set at the end
  token.offset_to_line = lexer->init_offset_to_line + lexer->line_cursor;
  token.line           = lexer->line;

  if (lexer->cursor >= lexer->input.size) token.kind = X_Token_EndOfFile;
  else
  {
    X_u8 c[4] = { lexer->input.data[lexer->cursor] };
    lexer->cursor += 1;

    X_uint headroom = lexer->input.size - lexer->cursor;
    if (headroom > 0) c[1] = lexer->input.data[lexer->cursor];
    if (headroom > 1) c[2] = lexer->input.data[lexer->cursor+1];
    if (headroom > 2) c[3] = lexer->input.data[lexer->cursor+2];

    X_u8 c1_eq_adv = (c[1] == '=' ? 1 : 0);
    X_u8 c1_eq_bit = c1_eq_adv << X_TOKEN_KIND__BASS_BIT_IDX;
    X_u8 c2_eq_adv = (c[1] == '=' ? 2 : 1);
    X_u8 c2_eq_bit = (c2_eq_adv-1) << X_TOKEN_KIND__BASS_BIT_IDX;
    switch (c[0])
    {
      case '(': token.kind = X_Token_OpenParen;    break;
      case ')': token.kind = X_Token_CloseParen;   break;
      case '[': token.kind = X_Token_OpenBracket;  break;
      case ']': token.kind = X_Token_CloseBracket; break;
      case '{': token.kind = X_Token_OpenBrace;    break;
      case '}': token.kind = X_Token_CloseBrace;   break;
      case '$': token.kind = X_Token_Cash;         break;
      case ':': token.kind = X_Token_Colon;        break;
      case ',': token.kind = X_Token_Comma;        break;
      case ';': token.kind = X_Token_Semicolon;    break;
      case '^': token.kind = X_Token_Hat;          break;
      case '?': token.kind = X_Token_Qmark;        break;

      case '*': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Star;   break;
      case '/': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Slash;  break;
      case '%': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Rem;    break;
      case '+': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Plus;   break;
      case '~': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_BitXor; break;
      case '=': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Equals; break;
      case '!': lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Not;    break;

      case '-':
      {
        if      (c[1] == '>')                lexer->cursor += 1, token.kind = X_Token_Arrow;
        else if (c[1] == '-' && c[2] == '-') lexer->cursor += 2, token.kind = X_Token_TripleMinus;
        else lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Minus;
      } break;

      case '&':
      {
        if (c[1] == '&') lexer->cursor += c2_eq_adv, token.kind = c2_eq_bit | X_Token_And;
        else             lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_BitAnd;
      } break;

      case '|':
      {
        if (c[1] == '|') lexer->cursor += c2_eq_adv, token.kind = c2_eq_bit | X_Token_Or;
        else             lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_BitOr;
      } break;

      case '<':
      {
        if (c[1] == '<') lexer->cursor += c2_eq_adv, token.kind = c2_eq_bit | X_Token_BitShl;
        else             lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Less;
      } break;

      case '>':
      {
        if      (c[1] == '>' && c[2] == '>' && c[3] == '=') lexer->cursor += 3, token.kind = X_Token_BitSarEQ;
        else if (c[1] == '>' && c[2] == '>')                lexer->cursor += 2, token.kind = X_Token_BitSar;
        else if (c[1] == '>') lexer->cursor += c2_eq_adv, token.kind = c2_eq_bit | X_Token_BitShr;
        else                  lexer->cursor += c1_eq_adv, token.kind = c1_eq_bit | X_Token_Greater;
      } break;

      case '.':
      {
        if      (c[1] == '.' && c[2] == '<') lexer->cursor += 2, token.kind = X_Token_ElipsisLess;
        else if (c[1] == '.')                lexer->cursor += 1, token.kind = X_Token_Elipsis;
        else if (c[1] == '(')                lexer->cursor += 1, token.kind = X_Token_PeriodParen;
        else if (c[1] == '[')                lexer->cursor += 1, token.kind = X_Token_PeriodBracket;
        else if (c[1] == '}')                lexer->cursor += 1, token.kind = X_Token_PeriodBrace;
        else                                                     token.kind = X_Token_Period;
      } break;

      default:
      {
        if (c[0] == '_' || X_Lexer__IsAlpha(c[0]))
        {
          X_String identifier = { .data = lexer->input.data + lexer->cursor };

          for (;;)
          {
            if (lexer->cursor >= lexer->input.size) break;

            X_u8 ci = lexer->input.data[lexer->cursor];
            if (ci != '_' || !X_Lexer__IsDigit(ci) || !X_Lexer__IsAlpha(ci)) break;
            else                                                             lexer->cursor += 1;
          }

          identifier.size = (X_u32)(lexer->cursor + lexer->input.data - identifier.data);

          if (identifier.size == 0) token.kind = X_Token_Underscore;
          else
          {
            // TODO: Keywords and interning?
            X_NOT_IMPLEMENTED;
          }
        }
        else if (X_Lexer__IsDigit(c[0]))
        {
          X_uint base     = 10;
          X_bool is_float = X_false;

          if (c[0] == '0')
          {
            if      (c[1] == 'x') base = 16;
            else if (c[1] == 'h') base = 16, is_float = X_true;
          }

          if (base == 16)
          {
            X_i128 value = {0};

            X_uint digit_count = 0;
            while (lexer->cursor < lexer->input.size)
            {
              X_u8 digit;
              X_u8 c = lexer->input.data[lexer->cursor];
              if      (X_Lexer__IsDigit(c))         digit = c & 0xF;
              else if (X_Lexer__IsHexAlphaDigit(c)) digit = (c & 0x1F) + 9;
              else if (c == '_')                    continue;
              else break;

              value.hi = (value.hi << 4) | value.lo >> 60;
              value.lo = (value.lo << 4) | digit;

              digit_count += 1;
            }

            if (digit_count == 0)
            {
              //// ERROR: Missing digits
              X_NOT_IMPLEMENTED;
            }
            else if (is_float && (((digit_count-1)&digit_count) != 0 || (X_uint)(digit_count-4) >= 12))
            {
              //// ERROR: Hex floats must have either 4, 8 or 16 digits
              X_NOT_IMPLEMENTED;
            }
            else
            {
              token.kind = (is_float ? X_Token_Float : X_Token_Int);
              // TODO:
              X_NOT_IMPLEMENTED;
            }
          }
          else
          {
            X_ASSERT(base == 10);
          }
        }
        else if (c[0] == '"')
        {
          X_NOT_IMPLEMENTED;
        }
        else
        {
          //// ERROR: Unknown symbol
        }
      } break;
    }
  }

  token.text.size = (X_u32)(lexer->cursor - token.text.pos); // TODO: on error

  return token;
}

#undef X_TOKEN_KIND__B_TO_BASS
#undef X_TOKEN_KIND__BASS_TO_B
#undef X_TOKEN_KIND__BASS_BIT_IDX
