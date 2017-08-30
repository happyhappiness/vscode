(!__archive_ppmd7_functions.Ppmd7_Alloc(&rar->ppmd7_context,
        rar->dictionary_size, &g_szalloc))
      {
        archive_set_error(&a->archive, ENOMEM,
                          "Out of memory");
        return (ARCHIVE_FATAL);
      }