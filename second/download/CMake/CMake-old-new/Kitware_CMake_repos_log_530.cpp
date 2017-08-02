archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "lzma compression failed:"
			    " lzma_code() call returned status %d",
			    ret)