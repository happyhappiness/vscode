{
		struct archive_read_filter *t = a->filter->upstream;
		free(a->filter);
		a->filter = t;
	}