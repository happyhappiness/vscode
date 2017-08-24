(data->in_buffer == data->in)
			return 0;
		else {
			size_t l = data->in - data->in_buffer;
			r = drive_compressor(f, data->in_buffer, l);
			if (r == ARCHIVE_OK)
				r = (ssize_t)l;
		}