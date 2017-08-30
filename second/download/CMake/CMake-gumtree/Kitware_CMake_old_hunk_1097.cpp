    /* Seems as though dictionary sizes are not used. Even so, minimize

     * memory usage as much as possible.

     */

    if (rar->unp_size >= DICTIONARY_MAX_SIZE)

      rar->dictionary_size = DICTIONARY_MAX_SIZE;

    else

      rar->dictionary_size = rar_fls(rar->unp_size) << 1;

    rar->lzss.window = (unsigned char *)realloc(rar->lzss.window,

                                                rar->dictionary_size);

    if (rar->lzss.window == NULL) {

      archive_set_error(&a->archive, ENOMEM,

                        "Unable to allocate memory for uncompressed data.");

      return (ARCHIVE_FATAL);

    }

    memset(rar->lzss.window, 0, rar->dictionary_size);

    rar->lzss.mask = rar->dictionary_size - 1;

  }

