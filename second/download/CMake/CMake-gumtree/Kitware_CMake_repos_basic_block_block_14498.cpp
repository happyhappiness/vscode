{
			ret = __archive_write_filter(f->next_filter,
			    data->compressed,
			    data->compressed_buffer_size);
			if (ret != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			data->stream.next_out = data->compressed;
			data->stream.avail_out =
			    (uInt)data->compressed_buffer_size;
		}