{
    /* Seems as though dictionary sizes are not used. Even so, minimize
     * memory usage as much as possible.
     */
    void *new_window;
    unsigned int new_size;

    if (rar->unp_size >= DICTIONARY_MAX_SIZE)
      new_size = DICTIONARY_MAX_SIZE;
    else
      new_size = rar_fls((unsigned int)rar->unp_size) << 1;
    new_window = realloc(rar->lzss.window, new_size);
    if (new_window == NULL) {
      archive_set_error(&a->archive, ENOMEM,
                        "Unable to allocate memory for uncompressed data.");
      return (ARCHIVE_FATAL);
    }
    rar->lzss.window = (unsigned char *)new_window;
    rar->dictionary_size = new_size;
    memset(rar->lzss.window, 0, rar->dictionary_size);
    rar->lzss.mask = rar->dictionary_size - 1;
  }