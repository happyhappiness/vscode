(!__archive_ppmd7_functions.PpmdRAR_RangeDec_Init(&rar->range_dec))
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Unable to initialize PPMd range decoder");
        return (ARCHIVE_FATAL);
      }