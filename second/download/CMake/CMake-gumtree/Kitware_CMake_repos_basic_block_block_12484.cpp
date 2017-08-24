{
      unsigned char highbyte, flagbits, flagbyte;
      unsigned fn_end, offset;

      end = filename_size;
      fn_end = filename_size * 2;
      filename_size = 0;
      offset = (unsigned)strlen(filename) + 1;
      highbyte = *(p + offset++);
      flagbits = 0;
      flagbyte = 0;
      while (offset < end && filename_size < fn_end)
      {
        if (!flagbits)
        {
          flagbyte = *(p + offset++);
          flagbits = 8;
        }

        flagbits -= 2;
        switch((flagbyte >> flagbits) & 3)
        {
          case 0:
            filename[filename_size++] = '\0';
            filename[filename_size++] = *(p + offset++);
            break;
          case 1:
            filename[filename_size++] = highbyte;
            filename[filename_size++] = *(p + offset++);
            break;
          case 2:
            filename[filename_size++] = *(p + offset + 1);
            filename[filename_size++] = *(p + offset);
            offset += 2;
            break;
          case 3:
          {
            char extra, high;
            uint8_t length = *(p + offset++);

            if (length & 0x80) {
              extra = *(p + offset++);
              high = (char)highbyte;
            } else
              extra = high = 0;
            length = (length & 0x7f) + 2;
            while (length && filename_size < fn_end) {
              unsigned cp = filename_size >> 1;
              filename[filename_size++] = high;
              filename[filename_size++] = p[cp] + extra;
              length--;
            }
          }
          break;
        }
      }
      if (filename_size > fn_end) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Invalid filename");
        return (ARCHIVE_FATAL);
      }
      filename[filename_size++] = '\0';
      filename[filename_size++] = '\0';

      /* Decoded unicode form is UTF-16BE, so we have to update a string
       * conversion object for it. */
      if (rar->sconv_utf16be == NULL) {
        rar->sconv_utf16be = archive_string_conversion_from_charset(
           &a->archive, "UTF-16BE", 1);
        if (rar->sconv_utf16be == NULL)
          return (ARCHIVE_FATAL);
      }
      fn_sconv = rar->sconv_utf16be;

      strp = filename;
      while (memcmp(strp, "\x00\x00", 2))
      {
        if (!memcmp(strp, "\x00\\", 2))
          *(strp + 1) = '/';
        strp += 2;
      }
      p += offset;
    }