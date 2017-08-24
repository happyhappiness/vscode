{
			tar->sparse_offset = tar_atol10(value, strlen(value));
			if (tar->sparse_numbytes != -1) {
				if (gnu_add_sparse_entry(a, tar,
				    tar->sparse_offset, tar->sparse_numbytes)
				    != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
				tar->sparse_offset = -1;
				tar->sparse_numbytes = -1;
			}
		}