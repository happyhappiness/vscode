{
      /* Convert CRLF -> LF explicitly.  The C FILE "t"ext mode
         does not convert newlines on all platforms.  Move any
         trailing CR to the start of the buffer for the next read. */
      size_t cr = lexer->cr;
      size_t n;
      buffer[0] = '\r';
      n = fread(buffer + cr, 1, bufferSize - cr, lexer->file);
      if (n) {
        char* o = buffer;
        const char* i = buffer;
        const char* e;
        n += cr;
        cr = (buffer[n - 1] == '\r') ? 1 : 0;
        e = buffer + n - cr;
        while (i != e) {
          if (i[0] == '\r' && i[1] == '\n') {
            ++i;
          }
          *o++ = *i++;
        }
        n = o - buffer;
      } else {
        n = cr;
        cr = 0;
      }
      lexer->cr = cr;
      return n;
    }