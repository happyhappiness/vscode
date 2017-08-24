{
        /* Valid continuation of utf-8 multibyte sequence */
        utf8_bytes_left--;
        utf8_codepoint <<= 6;
        utf8_codepoint |= ((unsigned int) c & 0x3f);

      }