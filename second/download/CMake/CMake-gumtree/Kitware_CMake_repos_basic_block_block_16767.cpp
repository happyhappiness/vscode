{
		if (value != NULL)
			mtree->keys |= keybit;
		else
			mtree->keys &= ~keybit;
		return (ARCHIVE_OK);
	}