{
		err = cab_read_header(a); 
		if (err < ARCHIVE_WARN)
			return (err);
		/* We've found the header. */
		cab->found_header = 1;
	}