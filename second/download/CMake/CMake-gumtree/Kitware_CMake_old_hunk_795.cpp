    ret = read_data_compressed(a, buff, size, offset);

    if (ret != ARCHIVE_OK && ret != ARCHIVE_WARN)

      __archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd7_context, &g_szalloc);

    break; 



  default:

    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

                      "Unsupported compression method for RAR file.");

    ret = ARCHIVE_FATAL;

    break; 

  }

  return (ret);

}

