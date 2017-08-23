{
	archive_entry_set_is_data_encrypted(entry, 1);
	rar->has_encrypted_entries = 1;
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "RAR encryption support unavailable.");
    /* Since it is only the data part itself that is encrypted we can at least
       extract information about the currently processed entry and don't need
       to return ARCHIVE_FATAL here. */
    /*return (ARCHIVE_FATAL);*/
  }