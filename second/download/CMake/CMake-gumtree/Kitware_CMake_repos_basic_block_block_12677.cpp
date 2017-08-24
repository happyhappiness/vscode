{
		/* Return the bytes we just read */
		*size = avail;
		*offset = info->offset;
		info->offset += *size;
		info->unconsumed = avail;
		return (ARCHIVE_OK);
	}