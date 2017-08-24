{
      /*
       * If FHD_UNICODE is set but no unicode data, this file name form
       * is UTF-8, so we have to update a string conversion object for
       * it accordingly.
       */
      if (rar->sconv_utf8 == NULL) {
        rar->sconv_utf8 = archive_string_conversion_from_charset(
           &a->archive, "UTF-8", 1);
        if (rar->sconv_utf8 == NULL)
          return (ARCHIVE_FATAL);
      }
      fn_sconv = rar->sconv_utf8;
      while ((strp = strchr(filename, '\\')) != NULL)
        *strp = '/';
      p += filename_size;
    }