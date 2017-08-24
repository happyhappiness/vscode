{
				/* Fully sparse file; insert a zero-length "data" entry */
				archive_entry_sparse_add_entry(entry, 0, 0);
			}