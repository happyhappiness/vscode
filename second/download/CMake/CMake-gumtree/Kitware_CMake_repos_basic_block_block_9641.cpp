{
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