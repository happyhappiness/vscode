{
		data->total_out +=
		    data->compressed_buffer_size - data->stream.avail_out;
		ret = __archive_write_filter(f->next_filter,
		    data->compressed,
		    data->compressed_buffer_size - data->stream.avail_out);
		if (f->code == ARCHIVE_FILTER_LZIP && ret == ARCHIVE_OK) {
			archive_le32enc(data->compressed, data->crc32);
			archive_le64enc(data->compressed+4, data->total_in);
			archive_le64enc(data->compressed+12, data->total_out + 20);
			ret = __archive_write_filter(f->next_filter,
			    data->compressed, 20);
		}
	}