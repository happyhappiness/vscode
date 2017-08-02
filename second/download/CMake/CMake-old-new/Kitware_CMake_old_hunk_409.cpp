	while (off_s < size) {
		off_s = lseek(*fd, off_s, SEEK_DATA);
		if (off_s == (off_t)-1) {
			if (errno == ENXIO)
				break;/* no more hole */
			archive_set_error(&a->archive, errno,
			    "lseek(SEEK_HOLE) failed");
			exit_sts = ARCHIVE_FAILED;
