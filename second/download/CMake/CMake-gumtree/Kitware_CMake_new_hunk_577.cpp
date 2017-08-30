			}
		}
		zip_entry->uncompressed_size = zip_entry->compressed_size = 0;

		if (__archive_read_consume(a, linkname_length) < 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Read error skipping symlink target name");
			return ARCHIVE_FATAL;
		}
	} else if (0 == (zip_entry->zip_flags & ZIP_LENGTH_AT_END)
	    || zip_entry->uncompressed_size > 0) {
		/* Set the size only if it's meaningful. */
