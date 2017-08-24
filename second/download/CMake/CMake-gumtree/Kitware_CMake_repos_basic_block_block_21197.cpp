{
          /* \n was not preceded by \r; print \r\n. */
          ENSURE_BUFFER_SPACE(2);
          utf16_buf[utf16_buf_used++] = L'\r';
          utf16_buf[utf16_buf_used++] = L'\n';
        }