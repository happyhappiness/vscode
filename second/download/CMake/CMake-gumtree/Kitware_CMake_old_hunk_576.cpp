			    "Truncated Zip file");

			return ARCHIVE_FATAL;

		}

		if (__archive_read_consume(a, linkname_length) < 0) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "Read error skipping symlink target name");

			return ARCHIVE_FATAL;

		}



		sconv = zip->sconv;

		if (sconv == NULL && (zip->entry->zip_flags & ZIP_UTF8_NAME))

