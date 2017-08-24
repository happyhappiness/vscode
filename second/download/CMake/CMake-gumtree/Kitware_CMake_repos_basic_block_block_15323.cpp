(mbs_fn)
		r = archive_mstring_copy_mbs(&mine->filename, filename);
	else
		r = archive_mstring_copy_wcs(&mine->filename, filename)