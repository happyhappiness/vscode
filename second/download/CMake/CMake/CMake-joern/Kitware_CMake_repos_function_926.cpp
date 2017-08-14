static int
setup_sparse_fiemap(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	char buff[4096];
	struct fiemap *fm;
	struct fiemap_extent *fe;
	int64_t size;
	int count, do_fiemap, iters;
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
	fm->fm_length = ~0ULL;;
	fm->fm_flags = FIEMAP_FLAG_SYNC;
	fm->fm_extent_count = count;
	do_fiemap = 1;
	size = archive_entry_size(entry);
	for (iters = 0; ; ++iters) {
		int i, r;

		r = ioctl(*fd, FS_IOC_FIEMAP, fm); 
		if (r < 0) {
			/* When something error happens, it is better we
			 * should return ARCHIVE_OK because an earlier
			 * version(<2.6.28) cannot perform FS_IOC_FIEMAP. */
			goto exit_setup_sparse_fiemap;
		}
		if (fm->fm_mapped_extents == 0) {
			if (iters == 0) {
				/* Fully sparse file; insert a zero-length "data" entry */
				archive_entry_sparse_add_entry(entry, 0, 0);
			}
			break;
		}
		fe = fm->fm_extents;
		for (i = 0; i < (int)fm->fm_mapped_extents; i++, fe++) {
			if (!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
				/* The fe_length of the last block does not
				 * adjust itself to its size files. */
				int64_t length = fe->fe_length;
				if (fe->fe_logical + length > (uint64_t)size)
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
exit_setup_sparse_fiemap:
	return (exit_sts);
}