typedef enum X_Error_Code
{
	X_Error__FirstLexerError,
	X_Error_Lexer_UnknownSymbol,
	X_Error_Lexer_NewlineBeforeStringTermination,
	X_Error_Lexer_UnterminatedString,
	X_Error_Lexer_FloatExponentTooManyDigits,
	X_Error_Lexer_FloatExponentNoDigits,
	X_Error__LastLexerError = ,
	//X_Error__FirstParserError,
	//X_Error__LastParserError = ,
	//X_Error__FirstCheckerError,
	//X_Error__LastCheckerError = ,
} X_Error_Code;

typedef struct X_Error_Report
{
	X_Error_Code code;
	X_String message;
} X_Error_Report;
