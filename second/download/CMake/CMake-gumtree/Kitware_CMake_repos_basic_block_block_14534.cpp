(l >= data->out_block_size) {
			ret = __archive_write_filter(f->next_filter,
			    data->out_buffer, data->out_block_size);
			l -= data->out_block_size;
			memcpy(data->out_buffer,
			    data->out_buffer + data->out_block_size, l);
			data->out = data->out_buffer + l;
			if (ret < ARCHIVE_WARN)
				break;
		}