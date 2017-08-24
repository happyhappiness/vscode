{
		/*
		 * Write the last block and the end of the stream data.
		 */

		/* Write End Of Stream. */
		memset(data->out, 0, 4); data->out += 4;
		/* Write Stream checksum if needed. */
		if (data->stream_checksum) {
			unsigned int checksum;
			checksum = __archive_xxhash.XXH32_digest(
					data->xxh32_state);
			data->xxh32_state = NULL;
			archive_le32enc(data->out, checksum);
			data->out += 4;
		}
		ret = __archive_write_filter(f->next_filter,
			    data->out_buffer, data->out - data->out_buffer);
	}