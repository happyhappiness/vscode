(r == 0) {
			archive_set_error(&a->archive, ENOMEM,
			    "Coludn't allocate memory for PPMd");
			return (ARCHIVE_FATAL);
		}