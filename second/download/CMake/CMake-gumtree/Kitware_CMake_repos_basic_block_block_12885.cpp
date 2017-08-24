(gnu_add_sparse_entry(a, tar,
				    tar->sparse_offset, tar->sparse_numbytes)
				    != ARCHIVE_OK)
					return (ARCHIVE_FATAL);