{
			/*
			 * Specify binary mode. We will not convert
			 * filenames, uname and gname to any charsets.
			 */
			pax->opt_binary = 1;
			ret = ARCHIVE_OK;
		}