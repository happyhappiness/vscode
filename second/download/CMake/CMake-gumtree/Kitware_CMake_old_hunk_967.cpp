    if (bytes_skipped < 0)
      return (ARCHIVE_FATAL);
  }
  return (ARCHIVE_OK);
}

static int
archive_read_format_rar_cleanup(struct archive_read *a)
{
