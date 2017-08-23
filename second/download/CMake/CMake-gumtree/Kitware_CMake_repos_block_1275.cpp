{
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for ZIP decryption");
			return (ARCHIVE_FATAL);
		}