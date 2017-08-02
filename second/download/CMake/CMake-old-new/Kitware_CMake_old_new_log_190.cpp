archive_set_error(&a->archive, 0,
		    "Too much data: Truncating file at %ju bytes", (uintmax_t)a->filesize)