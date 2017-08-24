{
			xar->outbuff = malloc(OUTBUFF_SIZE);
			if (xar->outbuff == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Couldn't allocate memory for out buffer");
				return (ARCHIVE_FATAL);
			}
		}