(start < end) {
			if (gnu_add_sparse_entry(a, tar, start,
			    end - start) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			tar->sparse_last->hole = hole;
		}