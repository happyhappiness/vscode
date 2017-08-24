(i = 0; i < cnt; i++) {
			archive_entry_sparse_next(entry, &offset, &length);
			if (offset - base >= 4096) {
				sparse = 1;/* we have a hole. */
				break;
			}
			base = offset + length;
		}