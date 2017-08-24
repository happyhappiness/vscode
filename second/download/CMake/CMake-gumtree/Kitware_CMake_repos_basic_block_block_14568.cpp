(lzo_version() < 0x940) {
		free(data);
		archive_set_error(_a, ARCHIVE_ERRNO_MISC,
		    "liblzo library is too old(%s < 0.940)",
		    lzo_version_string());
		return (ARCHIVE_FATAL);
	}