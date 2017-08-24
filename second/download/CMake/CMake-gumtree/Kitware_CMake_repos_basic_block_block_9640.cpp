(lseek(*fd, 0, SEEK_HOLE) == 0 &&
			lseek(*fd, 0, SEEK_END) == size) {
			/* Fully sparse file; insert a zero-length "data" entry */
			archive_entry_sparse_add_entry(entry, 0, 0);
		}