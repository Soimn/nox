#define X_AST_KIND__BLOCK(N) ((N) << 4)

#define X_AST_KIND__PRECEDENCE(K) ((K) >> 4)

typedef enum X_AST_Kind
{
  /// BLOCK 0
  X_AST_Invalid = 0,

  X_AST__FirstExpression,
  X_AST__FirstPrimaryExpression = X_AST__FirstExpression,
  X_AST_Identifier = X_AST__FirstPrimaryExpression,
  X_AST_String,
  X_AST_Int,
  X_AST_Float,
  X_AST_Compound,
  X_AST_StructType,
  X_AST_UnionType,
  X_AST_ProcType,
  X_AST_StructLit,
  X_AST_ArrayLit,
  X_AST_ProcLit,
  X_AST__PastLastPrimaryExpression,

  /// BLOCK 1
  X_AST__FirstPostfixLevel = X_AST_KIND__BLOCK(1),
  X_AST_Subscript = X_AST__FirstPostfixLevel,
  X_AST_Slice,
  X_AST_Member,
  X_AST_Dereference,
  X_AST_Call,
  X_AST__PastLastPostfixLevel,

  X_AST__FirstPrefixLevel,
  X_AST_Pos = X_AST__FirstPrefixLevel,
  X_AST_Neg,
  X_AST_Not,
  X_AST_BitNot,
  X_AST_Reference,
  X_AST__PastLastPrefixLevel,

  /// BLOCK 2
  X_AST__FirstBinaryOp = X_AST_KIND__BLOCK(2),
  X_AST__FirstMulLevel = X_AST__FirstBinaryOp,
  X_AST_Mul = X_AST__FirstMulLevel,
  X_AST_Div,
  X_AST_Rem,
  X_AST_BitAnd,
  X_AST_BitShr,
  X_AST_BitSar,
  X_AST_BitShl,
  X_AST__PastLastMulLevel,

  /// BLOCK 3
  X_AST__FirstAddLevel = X_AST_KIND__BLOCK(3),
  X_AST_Add = X_AST__FirstAddLevel,
  X_AST_Sub,
  X_AST_BitOr,
  X_AST_BitXor,
  X_AST__PastLastAddLevel,

  /// BLOCK 4
  X_AST__FirstCmpLevel = X_AST_KIND__BLOCK(4),
  X_AST_CmpEQ = X_AST__FirstCmpLevel,
  X_AST_CmpNotEQ,
  X_AST_CmpLess,
  X_AST_CmpLessEQ,
  X_AST_CmpGreater,
  X_AST_CmpGreaterEQ,
  X_AST__PastLastCmpLevel,

  /// BLOCK 5
  X_AST__FirstAndLevel = X_AST_KIND__BLOCK(5),
  X_AST_And = X_AST__FirstAndLevel,
  X_AST__PastLastAndLevel,

  /// BLOCK 6
  X_AST__FirstOrLevel = X_AST_KIND__BLOCK(6),
  X_AST_Or = X_AST__FirstOrLevel,
  X_AST__PastLastOrLevel,
  X_AST__PastLastBinaryOp = X_AST__PastLastOrLevel,

  /// BLOCK 7
  X_AST__FirstCondLevel = X_AST_KIND__BLOCK(7),
  X_AST_Conditional = X_AST__FirstCondLevel,
  X_AST__PastLastCondLevel,

  X_AST__PastLastExpression = X_AST__PastLastCondLevel,

  /// BLOCK 8-
  X_AST__FirstDeclaration = X_AST_KIND__BLOCK(8),
  X_AST_Var = X_AST__FirstDeclaration,
  X_AST_Const,
  X_AST__PastLastDeclaration,

  X_AST__FirstStatement,
  X_AST_If = X_AST__FirstStatement,
  X_AST_While,
  X_AST_Return,
  X_AST_Break,
  X_AST_Continue,
  X_AST_Assign,
  X_AST__PastLastStatement,
} X_AST_Kind;

#undef X_AST_KIND__BLOCK

X_STATIC_ASSERT(X_AST__PastLastPrimaryExpression <= X_AST__FirstPostfixLevel);
X_STATIC_ASSERT(X_AST__PastLastPostfixLevel      <= X_AST__FirstPrefixLevel);
X_STATIC_ASSERT(X_AST__PastLastPrefixLevel       <= X_AST__FirstMulLevel);
X_STATIC_ASSERT(X_AST__FirstBinaryOp             == X_AST__FirstMulLevel);
X_STATIC_ASSERT(X_AST__PastLastMulLevel          <= X_AST__FirstAddLevel);
X_STATIC_ASSERT(X_AST__PastLastAddLevel          <= X_AST__FirstCmpLevel);
X_STATIC_ASSERT(X_AST__PastLastCmpLevel          <= X_AST__FirstAndLevel);
X_STATIC_ASSERT(X_AST__PastLastAndLevel          <= X_AST__FirstOrLevel);
X_STATIC_ASSERT(X_AST__PastLastOrLevel           <= X_AST__FirstCondLevel);
X_STATIC_ASSERT(X_AST__PastLastOrLevel           == X_AST__PastLastBinaryOp);
X_STATIC_ASSERT(X_AST__PastLastCondLevel         == X_AST__PastLastExpression);

typedef struct X_AST
{
  X_AST_Kind kind;
  X_Text text;
} X_AST;
