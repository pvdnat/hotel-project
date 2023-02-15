 %{
#include "wish.h"
  int yylex();
  void yyerror(const char* s);
%}

%union {
  char *s;
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

%start cmdline

%%

cmdline: 
%empty  /* an empty line is valid, too! Do nothing */
| redir_prog bg_mode    
| in_prog pipe bg_mode  
| arg YY_SET arg 
| YY_PWD          
| YY_CD arg      
| YY_EXIT        { /* ... */ }

pipe: 
  YY_BAR out_prog  
| pipe YY_BAR out_prog 

redir_prog: 
  prog           
| prog any_redir 

in_prog:   
  prog           
| prog in_redir  

out_prog:   
  prog
| prog out_redir 

inout_redir:    
  in_redir out_redir
| out_redir in_redir

out_redir:
  out1_redir  
| out2_redir  

any_redir:
  in_redir    
| out_redir   
| inout_redir 

in_redir:   YY_LESS arg    
out1_redir: YY_MORE arg    
out2_redir: YY_MOREMORE arg 

bg_mode: 
%empty         
| YY_AMP

prog: 
  args

args:  
  arg
| args arg

arg: 
  YY_TOK

%%

/* This section is empty */
