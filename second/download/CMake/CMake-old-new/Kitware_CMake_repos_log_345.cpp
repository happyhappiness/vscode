archive_set_error(a, ENOMEM,
		    "lzma compression error:"
		    " %ju MiB would have been needed",
		    (uintmax_t)((lzma_memusage(strm) + 1024 * 1024 -1)
			/ (1024 * 1024)));