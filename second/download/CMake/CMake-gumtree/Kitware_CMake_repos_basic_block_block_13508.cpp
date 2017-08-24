(zip_entry->compressed_size == 0) {
			zip_entry->compressed_size
			    = zip_entry_central_dir.compressed_size;
		} else if (zip_entry->compressed_size
		    != zip_entry_central_dir.compressed_size) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Inconsistent compressed size: "
			    "%jd in central directory, %jd in local header",
			    (intmax_t)zip_entry_central_dir.compressed_size,
			    (intmax_t)zip_entry->compressed_size);
			ret = ARCHIVE_WARN;
		}