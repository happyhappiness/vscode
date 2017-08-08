{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't find the boot image file ``%s''",
		    iso9660->el_torito.boot_filename.s);
		return (ARCHIVE_FATAL);
	}