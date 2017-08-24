(lexer->string_buffer) {
      strcpy(lexer->string_buffer, text);
      lexer->string_position = lexer->string_buffer;
      lexer->string_left = length;
    } else {
      result = 0;
    }