{
    if (text && length < lexer->size) {
      strcpy(lexer->token.text, text);
      lexer->token.length = length;
      return;
    }
    free(lexer->token.text);
    lexer->token.text = 0;
    lexer->size = 0;
  }