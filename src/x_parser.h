typedef struct X_Parser
{
  X_Lexer lexer;
  X_Token tokens[2];

	X_Error_Report error_report;
} X_Parser;

X_Token
X_Parser_NextToken(X_Parser* state)
{
  // TODO: Maybe batch lex tokens?
  state->tokens[0] = state->tokens[1];
  state->tokens[1] = X_Lexer_NextToken(&state->lexer);
  return state->tokens[0];
}

#define X_GetToken() (state->tokens[0])
#define X_PeekToken() (state->tokens[1])
#define X_NextToken() X_Parser_NextToken(state)
#define X_IsToken(K) (state->tokens[0].kind == (K))
#define X_EatToken(K) (state->tokens[0].kind == (K) ? (X_NextToken(), X_true) : X_false)

void*
X_Parser_PushNode(X_Parser* state, X_AST_Kind kind)
{
  X_NOT_IMPLEMENTED;
  return 0;
}

X_bool X_Parser_ParseExpression(X_Parser* state, X_Expr** expr);

X_bool
X_Parser_ParsePrimaryExpr(X_Parser* state, X_Expr** expr)
{
  if (X_IsToken(X_Token_Identifier))
  {
    X_NOT_IMPLEMENTED;
  }
  else if (X_IsToken(X_Token_String))
  {
    X_NOT_IMPLEMENTED;
  }
  else if (X_IsToken(X_Token_Int))
  {
    X_Token token = X_GetToken();
    X_NextToken();

    *expr = X_Parser_PushNode(state, X_AST_Int);
    (*expr)->int_expr.value = token.integer;
  }
  else if (X_IsToken(X_Token_Float))
  {
    X_Token token = X_GetToken();
    X_NextToken();

    *expr = X_Parser_PushNode(state, X_AST_Float);
    (*expr)->float_expr.value = token.floating;
  }
  else if (X_EatToken(X_Token_OpenParen))
  {
    X_Expr* comp;
    if (!X_Parser_ParseExpression(state, &comp)) return X_false;

    if (!X_EatToken(X_Token_CloseParen))
    {
      //// ERROR: Missing closing paren
      X_NOT_IMPLEMENTED;
      return X_false;
    }

    *expr = X_Parser_PushNode(state, X_AST_Compound);
    (*expr)->compound_expr.expr = comp;
  }
  else if (X_EatToken(X_Token_Struct))
  {
    X_NOT_IMPLEMENTED;
  }
  else if (X_EatToken(X_Token_Proc))
  {
    X_NOT_IMPLEMENTED;
  }
  else if (X_EatToken(X_Token_PeriodBrace)) // NOTE: Parsed as primary to avoid special casing empty primary expression
  {
    X_NOT_IMPLEMENTED;
  }
  else if (X_EatToken(X_Token_PeriodBracket)) // NOTE: Parsed as primary to avoid special casing empty primary expression
  {
    X_NOT_IMPLEMENTED;
  }
  else
  {
    if (X_IsToken(X_Token_Invalid))
    {
      //// ERROR: Lexing error
      X_NOT_IMPLEMENTED;
      return X_false;
    }
    else
    {
      //// ERROR: Missing primary expression
      X_NOT_IMPLEMENTED;
      return X_false;
    }
  }

  return X_true;
}

X_bool
X_Parser_ParseTypePrefixExpr(X_Parser* state, X_Expr** expr)
{
  for (;;)
  {
    if (X_EatToken(X_Token_Hat))
    {
      *expr = X_Parser_PushNode(state, X_AST_PointerTo);
      expr = &(*expr)->unary_expr.operand;
    }
    else if (X_EatToken(X_Token_OpenBracket))
    {
      if (X_EatToken(X_Token_CloseBracket))
      {
        *expr = X_Parser_PushNode(state, X_AST_SliceOf);
        expr = &(*expr)->unary_expr.operand;
      }
      else
      {
        X_Expr* size;
        if (!X_Parser_ParseExpression(state, &size)) return X_false;
        else
        {
          *expr = X_Parser_PushNode(state, X_AST_ArrayOf);
          (*expr)->array_of_expr.size = size;

          expr = &(*expr)->array_of_expr.type;
        }
      }
    }
    else break;
  }

  return X_Parser_ParsePrimaryExpr(state, expr);
}

X_bool
X_Parser_ParsePostfixUnaryExpr(X_Parser* state, X_Expr** expr)
{
  if (!X_Parser_ParseTypePrefixExpr(state, expr)) return X_false;

  for (;;)
  {
    X_Expr* operand = *expr;

    if (X_EatToken(X_Token_Hat))
    {
      *expr = X_Parser_PushNode(state, X_AST_Dereference);
      (*expr)->unary_expr.operand = operand;
    }
    else if (X_EatToken(X_Token_OpenBracket))
    {
      X_Expr* first = 0;
      if (!X_IsToken(X_Token_Colon) && !X_Parser_ParseExpression(state, &first)) return X_false;

      if (!X_EatToken(X_Token_Colon))
      {
        if (!X_EatToken(X_Token_CloseBracket))
        {
          //// ERROR: Missing closing bracket after subscript
          X_NOT_IMPLEMENTED;
          return X_false;
        }

        *expr = X_Parser_PushNode(state, X_AST_Subscript);
        (*expr)->subscript_expr.array = operand;
        (*expr)->subscript_expr.index = first;
      }
      else
      {
        X_Expr* start_idx    = first;
        X_Expr* past_end_idx = 0;

        if      (!X_IsToken(X_Token_CloseBracket) && !X_Parser_ParseExpression(state, &past_end_idx)) return X_false;
        else if (!X_EatToken(X_Token_CloseBracket))
        {
          //// ERROR: Missing closing bracket after slice
          X_NOT_IMPLEMENTED;
          return X_false;
        }

        *expr = X_Parser_PushNode(state, X_AST_Slice);
        (*expr)->slice_expr.array        = operand;
        (*expr)->slice_expr.start_idx    = start_idx;
        (*expr)->slice_expr.past_end_idx = past_end_idx;
      }
    }
    else if (X_EatToken(X_Token_Period))
    {
      X_Expr* name;
      if (!X_Parser_ParseTypePrefixExpr(state, &name)) return X_false;
      else
      {
        *expr = X_Parser_PushNode(state, X_AST_Member);
        (*expr)->member_expr.operand = operand;
        (*expr)->member_expr.name    = name;
      }
    }
    else if (X_EatToken(X_Token_OpenParen))
    {
      X_NOT_IMPLEMENTED;
    }
    else if (X_EatToken(X_Token_PeriodBracket))
    {
      X_NOT_IMPLEMENTED;
    }
    else if (X_EatToken(X_Token_PeriodBrace))
    {
      X_NOT_IMPLEMENTED;
    }
    else break;
  }

  return X_true;
}

X_bool
X_Parser_ParsePrefixUnaryExpr(X_Parser* state, X_Expr** expr)
{
  for (;; expr = &(*expr)->unary_expr.operand)
  {
    if      (X_EatToken(X_Token_Plus))   *expr = X_Parser_PushNode(state, X_AST_Pos);
    else if (X_EatToken(X_Token_Minus))  *expr = X_Parser_PushNode(state, X_AST_Neg);
    else if (X_EatToken(X_Token_BitNot)) *expr = X_Parser_PushNode(state, X_AST_BitNot);
    else if (X_EatToken(X_Token_Not))    *expr = X_Parser_PushNode(state, X_AST_Not);
    else if (X_EatToken(X_Token_BitAnd)) *expr = X_Parser_PushNode(state, X_AST_Reference);
    else                                 break;
  }

  return X_Parser_ParsePostfixUnaryExpr(state, expr);
}

X_bool
X_Parser_ParseBinaryExpr(X_Parser* state, X_Expr** expr)
{
  if (!X_Parser_ParsePrefixUnaryExpr(state, expr)) return X_false;

  for (X_Token token = X_GetToken(); X_TOKEN_KIND__IS_BINARY_OP(token.kind);)
  {
    X_AST_Kind kind   = (X_AST_Kind)token.kind;
    X_uint precedence = X_AST_KIND__PRECEDENCE(kind);

    X_Expr* right;
    if (!X_Parser_ParsePrefixUnaryExpr(state, &right)) return X_false;

    X_Expr** slot = expr;
    while (X_AST_KIND__PRECEDENCE((*slot)->kind) > precedence)
    {
      X_ASSERT(X_ASTKind_IsBinaryExpr((*slot)->kind));
      slot = &(*slot)->binary_expr.right;
    }

    X_Expr* left = *slot;
    *slot = X_Parser_PushNode(state, kind);
    (*slot)->binary_expr.left  = left;
    (*slot)->binary_expr.right = right;
  }

  return X_true;
}

X_bool
X_Parser_ParseConditionalExpr(X_Parser* state, X_Expr** expr)
{
  if (!X_Parser_ParseBinaryExpr(state, expr)) return X_false;

  if (X_EatToken(X_Token_Qmark))
  {
    X_Expr* condition = *expr;
    X_Expr* then_expr;
    X_Expr* else_expr;

    if      (!X_Parser_ParseBinaryExpr(state, &then_expr)) return X_false;
    else if (!X_EatToken(X_Token_Qmark))
    {
      //// ERROR: Missing else expr
      X_NOT_IMPLEMENTED;
      return X_false;
    }
    else if (!X_Parser_ParseBinaryExpr(state, &else_expr)) return X_false;
    else
    {
      *expr = X_Parser_PushNode(state, X_AST_Conditional);
      (*expr)->conditional_expr.condition = condition;
      (*expr)->conditional_expr.then_expr = then_expr;
      (*expr)->conditional_expr.else_expr = else_expr;
    }
  }

  return X_true;
}

X_bool
X_Parser_ParseExpression(X_Parser* state, X_Expr** expr)
{
  return X_Parser_ParseConditionalExpr(state, expr);
}

#undef X_GetToken
#undef X_PeekToken
#undef X_NextToken
#undef X_EatToken
