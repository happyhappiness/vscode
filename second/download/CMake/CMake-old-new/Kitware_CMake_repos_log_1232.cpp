archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "GZip compression failed:"
			    " deflate() call returned status %d",
			    ret);