(;file != NULL; file = file->next) {
		r = (int)compress_out(a, file->utf16name, file->name_len+2,
			ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}