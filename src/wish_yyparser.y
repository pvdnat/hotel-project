%{
#include "wish.h"
int yylex();
 %}

%union {
  char *s;
  int i;
  arglist_t alist;
  prog_t *exe;
  redirection_t redir;
}

%token YY_SET
%token YY_EXIT
%token YY_JOBS
%token YY_PWD
%token YY_CD
%token YY_UNKNOWN
%token YY_LESS
%token YY_MORE
%token YY_MOREMORE
%token YY_AMP
%token YY_BAR
%token<s> YY_TOK
%type<redir> out_redir any_redir in_redir out1_redir out2_redir inout_redir
%type<alist> args
%type<i> bg_mode
%type<exe> exe out_exe in_exe redir_exe pipe

%start cmdline

%%

cmdline: 
%empty                 { /* an empty line is valid, too! Do nothing */ }
| redir_exe bg_mode    { spawn($1, $2); }
| in_exe pipe bg_mode  { last_exe($2)->prev = $1; spawn($2, $3);}
| YY_TOK YY_SET YY_TOK { wish_assign($1, $3); }
| YY_PWD                 /* TODO */
| YY_JOBS                /* TODO */
| YY_CD YY_TOK           /* TODO */
| YY_EXIT              { wish_exit = 1; }

pipe: 
  YY_BAR out_exe  { $$ = $2;}
| pipe YY_BAR out_exe { $$ = $3; $$->prev = $1;}

redir_exe: 
  exe           { $$ = $1; } 
| exe any_redir { $$ = $1; $$->redirection = $2; }

in_exe:   
  exe           { $$ = $1; }
| exe in_redir  { $$ = $1; $$->redirection = $2; }

out_exe:   
  exe           { $$ = $1; }
| exe out_redir { $$ = $1; $$->redirection = $2; } 

inout_redir:    
  in_redir out_redir { $$.in = $1.in; $$.out1 = $2.out1; $$.out2 = $2.out2; }
| out_redir in_redir { $$.in = $2.in; $$.out1 = $1.out1; $$.out2 = $1.out2; }

out_redir:
  out1_redir { $$ = $1; } 
| out2_redir { $$ = $1; } 

any_redir:
  in_redir    { $$ = $1; }
| out_redir   { $$ = $1; } 
| inout_redir { $$ = $1; }

in_redir:   YY_LESS YY_TOK     { $$.in = $2; $$.out1 = $$.out2 = NULL; }
out1_redir: YY_MORE YY_TOK     { $$.out1 = $2; $$.in = $$.out2 = NULL; }
out2_redir: YY_MOREMORE YY_TOK { $$.out2 = $2; $$.in = $$.out1 = NULL; }

bg_mode: 
%empty   { $$ = 0; }
| YY_AMP { $$ = 1; }

exe: 
args { $$ = create_program($1); }

args:  
  YY_TOK    { $$ = create_arglist($1); }
| args YY_TOK { $$ = add_to_arglist($1, $2); }

%%

