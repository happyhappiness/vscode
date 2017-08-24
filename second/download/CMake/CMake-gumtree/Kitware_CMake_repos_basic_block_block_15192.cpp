{
	struct archive_write_disk *a;

	a = (struct archive_write_disk *)calloc(1, sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->archive.magic = ARCHIVE_WRITE_DISK_MAGIC;
	/* We're ready to write a header immediately. */
	a->archive.state = ARCHIVE_STATE_HEADER;
	a->archive.vtable = archive_write_disk_vtable();
	a->start_time = time(NULL);
	/* Query and restore the umask. */
	umask(a->user_umask = umask(0));
	if (archive_wstring_ensure(&a->path_safe, 512) == NULL) {
		free(a);
		return (NULL);
	}
	return (&a->archive);
}