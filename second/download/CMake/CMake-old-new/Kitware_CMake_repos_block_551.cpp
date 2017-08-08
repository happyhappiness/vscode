{
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Unacceptable dictionary size for lzip: %d",
			    dict_size);
			return (ARCHIVE_FATAL);
		}