(utf8_codepoint == 0x0a && previous_eol != 0x0d) {
          /* \n was not preceded by \r; print \r\n. */
          ENSURE_BUFFER_SPACE(2);
          utf16_buf[utf16_buf_used++] = L'\r';
          utf16_buf[utf16_buf_used++] = L'\n';
        } else if (utf8_codepoint == 0x0d && previous_eol == 0x0a) {
          /* \n was followed by \r; do not print the \r, since */
          /* the source was either \r\n\r (so the second \r is */
          /* redundant) or was \n\r (so the \n was processed */
          /* by the last case and an \r automatically inserted). */
        } else {
          /* \r without \n; print \r as-is. */
          ENSURE_BUFFER_SPACE(1);
          utf16_buf[utf16_buf_used++] = (WCHAR) utf8_codepoint;
        }