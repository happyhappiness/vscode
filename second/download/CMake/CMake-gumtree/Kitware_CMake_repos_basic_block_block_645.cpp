(lexer->token.text) {
    memcpy(temp, lexer->token.text, lexer->token.length);
    free(lexer->token.text);
  }