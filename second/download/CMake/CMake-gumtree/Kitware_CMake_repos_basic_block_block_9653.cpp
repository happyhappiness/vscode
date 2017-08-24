{
	int64_t size;
	off_t initial_off;
	off_t off_s, off_e;
	int exit_sts = ARCHIVE_OK;
	int check_fully_sparse = 0;

	if (archive_entry_filetype(entry) != AE_IFREG
	    || archive_entry_size(entry) <= 0
	    || archive_entry_hardlink(entry) != NULL)
		return (ARCHIVE_OK);

	/* Does filesystem support the reporting of hole ? */
	if (*fd < 0 && a->tree != NULL) {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
		*fd = a->open_on_current_dir(a->tree, path,
				O_RDONLY | O_NONBLOCK);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
	}

	if (*fd >= 0) {
#ifdef _PC_MIN_HOLE_SIZE
		if (fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
#endif
		initial_off = lseek(*fd, 0, SEEK_CUR);
		if (initial_off != 0)
			lseek(*fd, 0, SEEK_SET);
	} else {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
			
#ifdef _PC_MIN_HOLE_SIZE
		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
#endif
		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
		__archive_ensure_cloexec_flag(*fd);
		initial_off = 0;
	}

#ifndef _PC_MIN_HOLE_SIZE
	/* Check if the underlying filesystem supports seek hole */
	off_s = lseek(*fd, 0, SEEK_HOLE);
	if (off_s < 0)
#if defined(HAVE_LINUX_FIEMAP_H)
		return setup_sparse_fiemap(a, entry, fd);
#else
		goto exit_setup_sparse;
#endif
	else if (off_s > 0)
		lseek(*fd, 0, SEEK_SET);
#endif

	off_s = 0;
	size = archive_entry_size(entry);
	while (off_s < size) {
		off_s = lseek(*fd, off_s, SEEK_DATA);
		if (off_s == (off_t)-1) {
			if (errno == ENXIO) {
				/* no more hole */
				if (archive_entry_sparse_count(entry) == 0) {
					/* Potentially a fully-sparse file. */
					check_fully_sparse = 1;
				}
				break;
			}
			archive_set_error(&a->archive, errno,
			    "lseek(SEEK_HOLE) failed");
			exit_sts = ARCHIVE_FAILED;
			goto exit_setup_sparse;
		}
		off_e = lseek(*fd, off_s, SEEK_HOLE);
		if (off_e == (off_t)-1) {
			if (errno == ENXIO) {
				off_e = lseek(*fd, 0, SEEK_END);
				if (off_e != (off_t)-1)
					break;/* no more data */
			}
			archive_set_error(&a->archive, errno,
			    "lseek(SEEK_DATA) failed");
			exit_sts = ARCHIVE_FAILED;
			goto exit_setup_sparse;
		}
		if (off_s == 0 && off_e == size)
			break;/* This is not sparse. */
		archive_entry_sparse_add_entry(entry, off_s,
			off_e - off_s);
		off_s = off_e;
	}

	if (check_fully_sparse) {
		if (lseek(*fd, 0, SEEK_HOLE) == 0 &&
			lseek(*fd, 0, SEEK_END) == size) {
			/* Fully sparse file; insert a zero-length "data" entry */
			archive_entry_sparse_add_entry(entry, 0, 0);
		}
	}
exit_setup_sparse:
	lseek(*fd, initial_off, SEEK_SET);
	return (exit_sts);
}