archive_set_error(f->archive, ENOMEM,
			    "lzma compression error: "
			    "%ju MiB would have been needed",
			    (uintmax_t)((lzma_memusage(&(data->stream))
				    + 1024 * 1024 -1)
				/ (1024 * 1024)))