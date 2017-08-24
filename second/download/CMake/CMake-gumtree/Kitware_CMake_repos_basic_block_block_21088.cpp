{
          /* Single UTF-16 character */
          char_len = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         &KEV.uChar.UnicodeChar,
                                         1,
                                         &handle->tty.rd.last_key[prefix_len],
                                         sizeof handle->tty.rd.last_key,
                                         NULL,
                                         NULL);
        }