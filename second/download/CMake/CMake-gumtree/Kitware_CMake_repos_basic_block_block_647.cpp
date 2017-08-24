{
      int length = lexer->string_left;
      if ((int)bufferSize < length) {
        length = (int)bufferSize;
      }
      memcpy(buffer, lexer->string_position, length);
      lexer->string_position += length;
      lexer->string_left -= length;
      return length;
    }