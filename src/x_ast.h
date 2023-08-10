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
  X_AST_ProcLit,
  X_AST__PastLastPrimaryExpression,

  /// BLOCK 1
  X_AST__FirstTypePrefixLevel = X_AST_KIND__BLOCK(1),
  X_AST_PointerTo = X_AST__FirstTypePrefixLevel,
  X_AST_SliceOf,
  X_AST_ArrayOf,
  X_AST__PastLastTypePrefixLevel,

  X_AST__FirstPostfixLevel = X_AST__PastLastTypePrefixLevel,
  X_AST_Dereference = X_AST__FirstPostfixLevel,
  X_AST_Subscript,
  X_AST_Slice,
  X_AST_Member,
  X_AST_Call,
  X_AST_StructLit,
  X_AST_ArrayLit, 
  X_AST__PastLastPostfixLevel,

  X_AST__FirstPrefixLevel = X_AST__PastLastPostfixLevel,
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
  X_AST_Empty = X_AST__FirstStatement,
  X_AST_Block,
  X_AST_If,
  X_AST_While,
  X_AST_Return,
  X_AST_Break,
  X_AST_Continue,
  X_AST_Assign,
  X_AST__PastLastStatement,
  X_AST_KIND__End,
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
X_STATIC_ASSERT(X_AST_KIND__End <= X_U8_MAX);

X_bool
X_ASTKind_IsBinaryExpr(X_AST_Kind kind)
{
  return ((X_u8)(kind - X_AST__FirstBinaryOp) < (X_u8)(X_AST__PastLastBinaryOp - X_AST__FirstBinaryOp));
}

typedef union X_AST X_AST;
typedef union X_Expr X_Expr;
typedef union X_Decl X_Decl;
typedef union X_Stmnt X_Stmnt;

typedef struct X_AST_Header
{
  X_AST_Kind kind;
} X_AST_Header;

typedef struct X_Expr_Header
{
  struct X_AST_Header;
} X_Expr_Header;

typedef struct X_Decl_Header
{
  struct X_AST_Header;
} X_Decl_Header;

typedef struct X_Stmnt_Header
{
  struct X_AST_Header;
} X_Stmnt_Header;


/// Special


typedef struct X_AST_Arg
{
  struct X_AST_Header;
  X_Expr* name;
  X_Expr* value;
} X_AST_Arg;


/// Expressions

typedef struct X_Expr_Identifier
{
  struct X_Expr_Header;
  X_String* string;
} X_Expr_Identifier;

typedef struct X_Expr_String
{
  struct X_Expr_Header;
  X_String* string;
} X_Expr_String;

typedef struct X_Expr_Int
{
  struct X_Expr_Header;
  X_i128 value;
} X_Expr_Int;

typedef struct X_Expr_Float
{
  struct X_Expr_Header;
  X_f64 value;
} X_Expr_Float;

typedef struct X_Expr_Compound
{
  struct X_Expr_Header;
  X_Expr* expr;
} X_Expr_Compound;

typedef struct X_Expr_Struct_Type
{
  struct X_Expr_Header;
  // members
} X_Expr_Struct_Type;

typedef struct X_Expr_Union_Type
{
  struct X_Expr_Header;
  // members
} X_Expr_Union_Type;

typedef struct X_Expr_Proc_Type
{
  struct X_Expr_Header;
  // name
  // params
  // ret
} X_Expr_Proc_Type;

typedef struct X_Expr_Struct_Lit
{
  struct X_Expr_Header;
  // name
  // args
} X_Expr_Struct_Lit;

typedef struct X_Expr_Union_Lit
{
  struct X_Expr_Header;
  // name
  // args
} X_Expr_Union_Lit;

typedef struct X_Expr_Proc_Lit
{
  struct X_Expr_Header;
  // name
  // params
  // ret
  X_Stmnt* body;
} X_Expr_Proc_Lit;

typedef struct X_Expr_Array_Of
{
  struct X_Expr_Header;
  X_Expr* size;
  X_Expr* type;
} X_Expr_Array_Of;

typedef struct X_Expr_Member
{
  struct X_Expr_Header;
  X_Expr* operand;
  X_Expr* name;
} X_Expr_Member;

typedef struct X_Expr_Unary
{
  struct X_Expr_Header;
  X_Expr* operand;
} X_Expr_Unary;

typedef struct X_Expr_Subscript
{
  struct X_Expr_Header;
  X_Expr* array;
  X_Expr* index;
} X_Expr_Subscript;

typedef struct X_Expr_Slice
{
  struct X_Expr_Header;
  X_Expr* array;
  X_Expr* start_idx;
  X_Expr* past_end_idx;
} X_Expr_Slice;

typedef struct X_Expr_Call
{
  struct X_Expr_Header;
  // args
} X_Expr_Call;

typedef struct X_Expr_Binary
{
  struct X_Expr_Header;
  X_Expr* left;
  X_Expr* right;
} X_Expr_Binary;

typedef struct X_Expr_Conditional
{
  struct X_Expr_Header;
  X_Expr* condition;
  X_Expr* then_expr;
  X_Expr* else_expr;
} X_Expr_Conditional;

typedef union X_Expr
{
  struct X_Expr_Header;
  X_Expr_Identifier identifier_expr;
  X_Expr_String string_expr;
  X_Expr_Int int_expr;
  X_Expr_Float float_expr;
  X_Expr_Compound compound_expr;
  X_Expr_Struct_Type struct_type_expr;
  X_Expr_Union_Type union_type_expr;
  X_Expr_Proc_Type proc_type_expr;
  X_Expr_Struct_Lit struct_lit_expr;
  X_Expr_Union_Lit union_lit_expr;
  X_Expr_Proc_Lit proc_lit_expr;
  X_Expr_Array_Of array_of_expr;
  X_Expr_Member member_expr;
  X_Expr_Unary unary_expr;
  X_Expr_Subscript subscript_expr;
  X_Expr_Slice slice_expr;
  X_Expr_Call call_expr;
  X_Expr_Binary binary_expr;
  X_Expr_Conditional conditional_expr;
} X_Expr;


/// Declarations


typedef struct X_Decl_Var
{
  struct X_Decl_Header;
  // names;
  X_Expr* type;
  // values
} X_Decl_Var;

typedef struct X_Decl_Const
{
  struct X_Decl_Header;
  // names;
  X_Expr* type;
  // values
} X_Decl_Const;

typedef union X_Decl
{
  struct X_Decl_Header;
  X_Decl_Var var_decl;
  X_Decl_Const const_decl;
} X_Decl;


/// Statements


// NOTE: This represents statements created by a ; with nothing before it
//       and is stored in the event of future metaprogramming markers for
//       statements (e.g. in jai syntax @insert_code_from_file("file.jai"); )
typedef struct X_Stmtn_Empty
{
  struct X_Stmnt_Header;
} X_Stmnt_Empty;

typedef struct X_Stmtn_Block
{
  struct X_Stmnt_Header;
  X_String* label;
  X_Stmnt* body;
} X_Stmnt_Block;

typedef struct X_Stmnt_If
{
  struct X_Stmnt_Header;
  X_String* label;
  X_Expr* condition;
  X_Stmnt* then_stmnt;
  X_Stmnt* else_stmnt;
} X_Stmnt_If;

typedef struct X_Stmnt_While
{
  struct X_Stmnt_Header;
  X_String* label;
  X_Expr* condition;
  X_Stmnt* body;
} X_Stmnt_While;

typedef struct X_Stmnt_Return
{
  struct X_Stmnt_Header;
  // parameter list?
} X_Stmnt_Return;

typedef struct X_Stmnt_Assign
{
  X_AST_Kind op; // NOTE: X_AST_Invalid means regular =, otherwise the binary op (e.g. X_AST_Add for +=)
  //X_Expr* lhs;
  //X_Expr* rhs;
} X_Stmnt_Assign;

typedef union X_Stmnt
{
  struct X_Stmnt_Header;
  X_Stmnt_If if_stmnt;
  X_Stmnt_While while_stmnt;
} X_Stmnt;


/// AST


typedef union X_AST
{
  struct X_AST_Header;
  X_Expr expr;
  X_Decl decl;
  X_Stmnt stmnt;
} X_AST;
