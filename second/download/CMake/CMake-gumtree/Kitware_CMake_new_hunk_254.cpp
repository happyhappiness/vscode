  archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,

                      "archive_read_support_format_rar");



  rar = (struct rar *)calloc(sizeof(*rar), 1);

  if (rar == NULL)

  {

    archive_set_error(&a->archive, ENOMEM, "Can't allocate rar data");

    return (ARCHIVE_FATAL);

  }



	/*

	 * Until enough data has been read, we cannot tell about

