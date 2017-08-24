{
          /* \r without \n; print \r as-is. */
          ENSURE_BUFFER_SPACE(1);
          utf16_buf[utf16_buf_used++] = (WCHAR) utf8_codepoint;
        }