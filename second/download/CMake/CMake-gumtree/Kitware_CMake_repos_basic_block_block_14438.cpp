{
			ret = __archive_write_filter(f->next_filter,
			    data->compressed,
			    data->compressed_buffer_size);
			if (ret != ARCHIVE_OK) {
				/* TODO: Handle this write failure */
				return (ARCHIVE_FATAL);
			}
			data->stream.next_out = data->compressed;
			data->stream.avail_out = data->compressed_buffer_size;
		}