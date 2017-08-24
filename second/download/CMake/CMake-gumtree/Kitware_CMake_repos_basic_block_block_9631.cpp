(!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
				/* The fe_length of the last block does not
				 * adjust itself to its size files. */
				int64_t length = fe->fe_length;
				if (fe->fe_logical + length > (uint64_t)size)
					length -= fe->fe_logical + length - size;
				if (fe->fe_logical == 0 && length == size) {
					/* This is not sparse. */
					do_fiemap = 0;
					break;
				}
				if (length > 0)
					archive_entry_sparse_add_entry(entry,
					    fe->fe_logical, length);
			}