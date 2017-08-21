  archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
                      "archive_read_support_format_rar");

  rar = (struct rar *)malloc(sizeof(*rar));
  if (rar == NULL)
  {
    archive_set_error(&a->archive, ENOMEM, "Can't allocate rar data");
    return (ARCHIVE_FATAL);
  }
  memset(rar, 0, sizeof(*rar));

	/*
	 * Until enough data has been read, we cannot tell about
