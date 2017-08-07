{
			archive_mstring_get_mbs(a, &mine->filename, &mbs);
			archive_set_error(a, errno,
			    "Can't convert '%s' to WCS", mbs);
		}