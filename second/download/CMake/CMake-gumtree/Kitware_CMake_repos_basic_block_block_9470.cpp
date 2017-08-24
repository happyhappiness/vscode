{
	int tempfd = -1;
	int copyfile_flags = COPYFILE_NOFOLLOW | COPYFILE_ACL | COPYFILE_XATTR;
	struct stat copyfile_stat;
	int ret = ARCHIVE_OK;
	void *buff = NULL;
	int have_attrs;
	const char *name, *tempdir;
	struct archive_string tempfile;

	(void)fd; /* UNUSED */
	name = archive_entry_sourcepath(entry);
	if (name == NULL)
		name = archive_entry_pathname(entry);
	else if (a->tree != NULL && a->tree_enter_working_dir(a->tree) != 0) {
		archive_set_error(&a->archive, errno,
			    "Can't change dir to read extended attributes");
			return (ARCHIVE_FAILED);
	}
	if (name == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't open file to read extended attributes: No name");
		return (ARCHIVE_WARN);
	}

	/* Short-circuit if there's nothing to do. */
	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
	if (have_attrs == -1) {
		archive_set_error(&a->archive, errno,
			"Could not check extended attributes");
		return (ARCHIVE_WARN);
	}
	if (have_attrs == 0)
		return (ARCHIVE_OK);

	tempdir = NULL;
	if (issetugid() == 0)
		tempdir = getenv("TMPDIR");
	if (tempdir == NULL)
		tempdir = _PATH_TMP;
	archive_string_init(&tempfile);
	archive_strcpy(&tempfile, tempdir);
	archive_strcat(&tempfile, "tar.md.XXXXXX");
	tempfd = mkstemp(tempfile.s);
	if (tempfd < 0) {
		archive_set_error(&a->archive, errno,
		    "Could not open extended attribute file");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}
	__archive_ensure_cloexec_flag(tempfd);

	/* XXX I wish copyfile() could pack directly to a memory
	 * buffer; that would avoid the temp file here.  For that
	 * matter, it would be nice if fcopyfile() actually worked,
	 * that would reduce the many open/close races here. */
	if (copyfile(name, tempfile.s, 0, copyfile_flags | COPYFILE_PACK)) {
		archive_set_error(&a->archive, errno,
		    "Could not pack extended attributes");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}
	if (fstat(tempfd, &copyfile_stat)) {
		archive_set_error(&a->archive, errno,
		    "Could not check size of extended attributes");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}
	buff = malloc(copyfile_stat.st_size);
	if (buff == NULL) {
		archive_set_error(&a->archive, errno,
		    "Could not allocate memory for extended attributes");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}
	if (copyfile_stat.st_size != read(tempfd, buff, copyfile_stat.st_size)) {
		archive_set_error(&a->archive, errno,
		    "Could not read extended attributes into memory");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}
	archive_entry_copy_mac_metadata(entry, buff, copyfile_stat.st_size);

cleanup:
	if (tempfd >= 0) {
		close(tempfd);
		unlink(tempfile.s);
	}
	archive_string_free(&tempfile);
	free(buff);
	return (ret);
}