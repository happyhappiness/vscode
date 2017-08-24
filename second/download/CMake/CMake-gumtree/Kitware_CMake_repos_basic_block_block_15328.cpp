(mbs != NULL)
			archive_set_error(a, errno, "Couldn't stat '%s'", mbs);
		else
			archive_set_error(a, errno, "Couldn't stat '%S'", wcs)