{
		/* Consume as much as the decompressor actually used. */
		__archive_read_consume(a, lha->entry_unconsumed);
		lha->entry_unconsumed = 0;
	}