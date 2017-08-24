{
      free(lexer->string_buffer);
      lexer->string_buffer = 0;
      lexer->string_left = 0;
      lexer->string_position = 0;
    }