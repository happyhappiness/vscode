(parent_len > 240
		    || np->mb_len > 240
		    || parent_len + np->mb_len > 240) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "The regulation of Joliet extensions;"
			    " A length of a full-pathname of `%s' is "
			    "longer than 240 bytes, (p=%d, b=%d)",
			    archive_entry_pathname(np->file->entry),
			    (int)parent_len, (int)np->mb_len);
			return (ARCHIVE_FATAL);
		}