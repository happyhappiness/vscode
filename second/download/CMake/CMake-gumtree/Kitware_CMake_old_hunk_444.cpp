
		if (bytes_read == -1) {
			archive_set_error(f->archive, errno,
			    "Read from filter failed unexpectedly.");
			ret = ARCHIVE_FATAL;
			goto cleanup;
		}
