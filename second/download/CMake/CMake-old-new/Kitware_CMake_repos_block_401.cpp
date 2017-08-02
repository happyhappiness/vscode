{
			free(strm);
			lastrm->real_stream = NULL;
			archive_set_error(a, ENOMEM,
			    "Cannot allocate memory");
			return (ARCHIVE_FATAL);
		}