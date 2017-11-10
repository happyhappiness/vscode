static char *inflate_it(const void *data, unsigned long size,
			unsigned long inflated_size)
{
	git_zstream stream;
	void *out;
	int st;

	memset(&stream, 0, sizeof(stream));

	stream.next_in = (unsigned char *)data;
	stream.avail_in = size;
	stream.next_out = out = xmalloc(inflated_size);
	stream.avail_out = inflated_size;
	git_inflate_init(&stream);
	st = git_inflate(&stream, Z_FINISH);
	git_inflate_end(&stream);
	if ((st != Z_STREAM_END) || stream.total_out != inflated_size) {
		free(out);
		return NULL;
	}
	return out;
}