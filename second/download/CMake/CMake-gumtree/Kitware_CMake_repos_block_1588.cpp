{
		tar_flush_unconsumed(a, unconsumed);
		archive_set_error(&a->archive, EINVAL, "Damaged tar archive");
		return (ARCHIVE_RETRY); /* Retryable: Invalid header */
	}