{
			/* "size" is the size of the data in the entry. */
			tar->entry_bytes_remaining
			    = tar_atol10(value, strlen(value));
			/*
			 * But, "size" is not necessarily the size of
			 * the file on disk; if this is a sparse file,
			 * the disk size may have already been set from
			 * GNU.sparse.realsize or GNU.sparse.size or
			 * an old GNU header field or SCHILY.realsize
			 * or ....
			 */
			if (tar->realsize < 0) {
				archive_entry_set_size(entry,
				    tar->entry_bytes_remaining);
				tar->realsize
				    = tar->entry_bytes_remaining;
			}
		}