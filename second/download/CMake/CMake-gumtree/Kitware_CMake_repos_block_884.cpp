{
			archive_set_error(&a->archive, ENOMEM,
			    "Couldn't read link data");
			return (ARCHIVE_FAILED);
		}