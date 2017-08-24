(outbytes != xattr->size) {
			archive_set_error(&(a->archive), ARCHIVE_ERRNO_MISC,
			    "Decompressed size error");
			r = ARCHIVE_FATAL;
			break;
		}