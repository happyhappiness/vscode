
static int
setup_sparse(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	char buff[4096];
	struct fiemap *fm;
	struct fiemap_extent *fe;
	int64_t size;
	int count, do_fiemap;
	int exit_sts = ARCHIVE_OK;

	if (archive_entry_filetype(entry) != AE_IFREG
	    || archive_entry_size(entry) <= 0
	    || archive_entry_hardlink(entry) != NULL)
		return (ARCHIVE_OK);

	if (*fd < 0) {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
		if (a->tree != NULL)
			*fd = a->open_on_current_dir(a->tree, path,
				O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		else
			*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
		__archive_ensure_cloexec_flag(*fd);
	}

	/* Initialize buffer to avoid the error valgrind complains about. */
	memset(buff, 0, sizeof(buff));
	count = (sizeof(buff) - sizeof(*fm))/sizeof(*fe);
	fm = (struct fiemap *)buff;
	fm->fm_start = 0;
