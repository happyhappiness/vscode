{
    lexer->token.text = strdup(text);
    lexer->token.length = length;
    lexer->size = length + 1;
  }