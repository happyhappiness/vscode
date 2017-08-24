{
  cmListFileLexer* lexer = (cmListFileLexer*)malloc(sizeof(cmListFileLexer));
  if (!lexer) {
    return 0;
  }
  memset(lexer, 0, sizeof(*lexer));
  lexer->line = 1;
  lexer->column = 1;
  return lexer;
}