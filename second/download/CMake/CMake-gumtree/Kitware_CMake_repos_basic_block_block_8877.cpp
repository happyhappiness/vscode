{
		archive_copy_error(&(a->archive), ar);
		archive_read_free(ar);
		archive_string_free(&as);
		return (r);
	}