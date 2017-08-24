{
		data->child_buf_len = 65536;
		data->child_buf_avail = 0;
		data->child_buf = malloc(data->child_buf_len);

		if (data->child_buf == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate compression buffer");
			return (ARCHIVE_FATAL);
		}
	}