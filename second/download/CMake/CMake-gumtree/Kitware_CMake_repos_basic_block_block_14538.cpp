{
			unsigned int checksum;
			checksum = __archive_xxhash.XXH32_digest(
					data->xxh32_state);
			data->xxh32_state = NULL;
			archive_le32enc(data->out, checksum);
			data->out += 4;
		}