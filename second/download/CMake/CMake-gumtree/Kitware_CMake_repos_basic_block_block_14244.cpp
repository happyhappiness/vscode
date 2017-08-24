{
	struct archive_string temp_name;
	int fd = -1;

	archive_string_init(&temp_name);
	if (tmpdir == NULL) {
		if (get_tempdir(&temp_name) != ARCHIVE_OK)
			goto exit_tmpfile;
	} else {
		archive_strcpy(&temp_name, tmpdir);
		if (temp_name.s[temp_name.length-1] != '/')
			archive_strappend_char(&temp_name, '/');
	}
	archive_strcat(&temp_name, "libarchive_XXXXXX");
	fd = mkstemp(temp_name.s);
	if (fd < 0)
		goto exit_tmpfile;
	__archive_ensure_cloexec_flag(fd);
	unlink(temp_name.s);
exit_tmpfile:
	archive_string_free(&temp_name);
	return (fd);
}