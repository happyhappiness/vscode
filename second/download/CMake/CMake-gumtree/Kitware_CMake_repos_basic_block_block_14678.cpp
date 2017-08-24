{
			archive_le32enc(data->compressed, data->crc32);
			archive_le64enc(data->compressed+4, data->total_in);
			archive_le64enc(data->compressed+12, data->total_out + 20);
			ret = __archive_write_filter(f->next_filter,
			    data->compressed, 20);
		}