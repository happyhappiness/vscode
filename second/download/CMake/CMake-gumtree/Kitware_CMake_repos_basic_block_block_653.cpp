{
    cmListFileLexer_yylex_init(&lexer->scanner);
    cmListFileLexer_yyset_extra(lexer, lexer->scanner);
  }