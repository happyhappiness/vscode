{
			archive_mstring_get_wcs(a, &mine->filename, &wcs);
			archive_set_error(a, errno,
			    "Can't convert '%S' to MBS", wcs);
		}