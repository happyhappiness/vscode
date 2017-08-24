{
		/* The buffer is compressed. */
		archive_le32enc(data->out, outsize);
		data->out += 4;
	}