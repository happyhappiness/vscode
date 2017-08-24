{
		data->work_buffer = (lzo_voidp)malloc(data->work_buffer_size);
		if (data->work_buffer == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}