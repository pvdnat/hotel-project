%{
#include "wish.h"
#include "wish_yyparser.tab.h"
#ifdef __APPLE__
extern int yylex(void);
extern int yyparse(void);
#endif

char *wish_safe_getenv(char *s);
%}

%option noyywrap

digit         [0-9]
letter        [a-zA-Z_]
alnum         {digit}|{letter}
string        \"([^\n\\\"]|\\.)*\"
quoted_string \'([^\n\\\']|\\.)*\'
permitted     {digit}|{letter}|[-%@_+\[\]\\/,\.:]
unsupported   [;()*^?~{}`]

%%
"#".*"\n"?      { /* comment */ }

exit            { return YY_EXIT; }
pwd             { return YY_PWD;  }
cd              { return YY_CD;   }

\${alnum}+      { yylval.s = super_strdup(wish_safe_getenv(yytext + 1));
                  return YY_TOK; }
{permitted}+    { yylval.s = super_strdup(yytext);
                  return YY_TOK; }
{quoted_string} { yytext[yyleng - 1] = 0;
                  yylval.s = super_strdup(yytext + 1);
                  return YY_TOK; }
{string}        { yytext[yyleng - 1] = 0;
                  yylval.s = super_strdup(wish_unquote(yytext + 1));
                  return YY_TOK; }

"<"             { return YY_LESS;     }
">"             { return YY_MORE;     }
">>"            { return YY_MOREMORE; }
"&"             { return YY_AMP;      }
"|"             { return YY_BAR;      }
"="             { return YY_SET;      }

{unsupported}   { fprintf(stderr, "Unsupported command: %c\n", yytext[0]);
                  return YY_UNKNOWN;}
[\t\n\b\v ]+    { /* whitespaces */ }

.               { fprintf(stderr, "Illegal character: %c\n", yytext[0]);
                  return YY_UNKNOWN; }

%%

// The function returns 0 if there are no syntax errors and 1, otherwise
int wish_parse_command(char *command) {
  YY_BUFFER_STATE buffer = yy_scan_string(command);
  int retval = yyparse();
  yylex_destroy();
  return retval;
}
