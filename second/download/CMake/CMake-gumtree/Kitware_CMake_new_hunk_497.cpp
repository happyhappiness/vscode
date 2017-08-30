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

