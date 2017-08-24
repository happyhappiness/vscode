(flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
			fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
			    "Path is ", "absolute");
			return (ARCHIVE_FAILED);
		}