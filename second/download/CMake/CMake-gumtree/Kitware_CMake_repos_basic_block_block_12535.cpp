((length = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
              &rar->ppmd7_context, &rar->range_dec.p)) < 0)
            {
              archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                "Invalid symbol");
              return (ARCHIVE_FATAL);
            }