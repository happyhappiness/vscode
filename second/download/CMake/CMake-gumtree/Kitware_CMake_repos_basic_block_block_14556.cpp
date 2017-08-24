{
		unsigned int checksum =
		    __archive_xxhash.XXH32(data->out - outsize, outsize, 0);
		archive_le32enc(data->out, checksum);
		data->out += 4;
	}