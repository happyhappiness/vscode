{
    cmListFileLexer_yylex_destroy(lexer->scanner);
    if (lexer->file) {
      fclose(lexer->file);
      lexer->file = 0;
    }
    if (lexer->string_buffer) {
      free(lexer->string_buffer);
      lexer->string_buffer = 0;
      lexer->string_left = 0;
      lexer->string_position = 0;
    }
  }