{
    case ARCHIVE_FILTER_NONE:
      /* No filter to add, so do nothing.
       * NOTE: An initial "NONE" type filter is always set at the end of the
       * filter chain.
       */
      r1 = (ARCHIVE_OK);
      break;
    case ARCHIVE_FILTER_GZIP:
      strcpy(str, "gzip");
      r1 = archive_read_support_filter_gzip(_a);
      break;
    case ARCHIVE_FILTER_BZIP2:
      strcpy(str, "bzip2");
      r1 = archive_read_support_filter_bzip2(_a);
      break;
    case ARCHIVE_FILTER_COMPRESS:
      strcpy(str, "compress (.Z)");
      r1 = archive_read_support_filter_compress(_a);
      break;
    case ARCHIVE_FILTER_PROGRAM:
      archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
          "Cannot append program filter using archive_read_append_filter");
      return (ARCHIVE_FATAL);
    case ARCHIVE_FILTER_LZMA:
      strcpy(str, "lzma");
      r1 = archive_read_support_filter_lzma(_a);
      break;
    case ARCHIVE_FILTER_XZ:
      strcpy(str, "xz");
      r1 = archive_read_support_filter_xz(_a);
      break;
    case ARCHIVE_FILTER_UU:
      strcpy(str, "uu");
      r1 = archive_read_support_filter_uu(_a);
      break;
    case ARCHIVE_FILTER_RPM:
      strcpy(str, "rpm");
      r1 = archive_read_support_filter_rpm(_a);
      break;
    case ARCHIVE_FILTER_LZ4:
      strcpy(str, "lz4");
      r1 = archive_read_support_filter_lz4(_a);
      break;
    case ARCHIVE_FILTER_LZIP:
      strcpy(str, "lzip");
      r1 = archive_read_support_filter_lzip(_a);
      break;
    case ARCHIVE_FILTER_LRZIP:
      strcpy(str, "lrzip");
      r1 = archive_read_support_filter_lrzip(_a);
      break;
    default:
      archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
          "Invalid filter code specified");
      return (ARCHIVE_FATAL);
  }