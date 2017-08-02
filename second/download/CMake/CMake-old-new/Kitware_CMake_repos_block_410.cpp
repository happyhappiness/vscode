{
		free(strm->buff);
		free(strm);
		free(props);
		archive_set_error(a, ENOMEM,
		    "Coludn't allocate memory for PPMd");
		return (ARCHIVE_FATAL);
	}