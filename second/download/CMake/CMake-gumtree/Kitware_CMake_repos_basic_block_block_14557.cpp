{
		/* The buffer is not compressed. The compressed size was
		 * bigger than its uncompressed size. */
		archive_le32enc(data->out, length | 0x80000000);
		data->out += 4;
		memcpy(data->out, p, length);
		outsize = length;
	}