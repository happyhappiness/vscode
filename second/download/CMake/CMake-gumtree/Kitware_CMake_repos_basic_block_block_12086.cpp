{
		hf->bitlen = malloc(len_size * sizeof(hf->bitlen[0]));
		if (hf->bitlen == NULL)
			return (ARCHIVE_FATAL);
	}