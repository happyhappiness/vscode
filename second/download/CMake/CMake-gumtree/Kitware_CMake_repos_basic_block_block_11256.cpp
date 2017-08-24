{
		*buff = NULL;
		*size = 0;
		*offset = cab->entry_offset;
		cab->end_of_entry = 1;
		return (ARCHIVE_OK);
	}