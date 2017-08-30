			return (ARCHIVE_FATAL);

		}

	}

	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

	    "Input requires too many filters for decoding");

	return (ARCHIVE_FATAL);

}



/*

