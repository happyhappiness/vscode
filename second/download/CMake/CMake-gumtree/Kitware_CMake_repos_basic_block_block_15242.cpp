{
	struct archive_write_disk *a;
	int ret;
	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_write_disk_free");
	a = (struct archive_write_disk *)_a;
	ret = _archive_write_disk_close(&a->archive);
	archive_write_disk_set_group_lookup(&a->archive, NULL, NULL, NULL);
	archive_write_disk_set_user_lookup(&a->archive, NULL, NULL, NULL);
	if (a->entry)
		archive_entry_free(a->entry);
	archive_wstring_free(&a->_name_data);
	archive_string_free(&a->archive.error_string);
	archive_wstring_free(&a->path_safe);
	a->archive.magic = 0;
	__archive_clean(&a->archive);
	free(a);
	return (ret);
}