(archive_entry_sparse_count(entry) == 0) {
					/* Potentially a fully-sparse file. */
					check_fully_sparse = 1;
				}