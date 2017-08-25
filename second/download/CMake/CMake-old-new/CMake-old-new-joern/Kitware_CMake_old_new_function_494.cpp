static int
setup_sparse(struct archive_read_disk *a,
    struct archive_entry *entry, int fd)
{
	char buff[4096];
	struct fiemap *fm;
	struct fiemap_extent *fe;
	int64_t size;
	int count, do_fiemap;
	int initial_fd = fd;
	int exit_sts = ARCHIVE_OK;

	if (archive_entry_filetype(entry) != AE_IFREG
	    || archive_entry_size(entry) <= 0
	    || archive_entry_hardlink(entry) != NULL)
		return (ARCHIVE_OK);

	if (fd < 0) {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
		fd = open(path, O_RDONLY | O_NONBLOCK);
		if (fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
	}

	count = (sizeof(buff) - sizeof(*fm))/sizeof(*fe);
	fm = (struct fiemap *)buff;
	fm->fm_start = 0;
	fm->fm_length = ~0ULL;;
	fm->fm_flags = FIEMAP_FLAG_SYNC;
	fm->fm_extent_count = count;
	do_fiemap = 1;
	size = archive_entry_size(entry);
	for (;;) {
		int i, r;

		r = ioctl(fd, FS_IOC_FIEMAP, fm); 
		if (r < 0) {
			/* When errno is ENOTTY, it is better we should
			 * return ARCHIVE_OK because an earlier version
			 *(<2.6.28) cannot perfom FS_IOC_FIEMAP.
			 * We should also check if errno is EOPNOTSUPP,
			 * it means "Operation not supported". */
			if (errno != ENOTTY && errno != EOPNOTSUPP) {
				archive_set_error(&a->archive, errno,
				    "FIEMAP failed");
				exit_sts = ARCHIVE_FAILED;
			}
			goto exit_setup_sparse;
		}
		if (fm->fm_mapped_extents == 0)
			break;
		fe = fm->fm_extents;
		for (i = 0; i < fm->fm_mapped_extents; i++, fe++) {
			if (!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
				/* The fe_length of the last block does not
				 * adjust itself to its size files. */
				int64_t length = fe->fe_length;
				if (fe->fe_logical + length > size)
					length -= fe->fe_logical + length - size;
				if (fe->fe_logical == 0 && length == size) {
					/* This is not sparse. */
					do_fiemap = 0;
					break;
				}
				if (length > 0)
					archive_entry_sparse_add_entry(entry,
					    fe->fe_logical, length);
			}
			if (fe->fe_flags & FIEMAP_EXTENT_LAST)
				do_fiemap = 0;
		}
		if (do_fiemap) {
			fe = fm->fm_extents + fm->fm_mapped_extents -1;
			fm->fm_start = fe->fe_logical + fe->fe_length;
		} else
			break;
	}
exit_setup_sparse:
	if (initial_fd != fd)
		close(fd);
	return (exit_sts);
}