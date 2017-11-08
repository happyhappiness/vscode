static unsigned char *deflate_it(char *data,
				 unsigned long size,
				 unsigned long *result_size)
{
	int bound;
	unsigned char *deflated;
	git_zstream stream;

	git_deflate_init(&stream, zlib_compression_level);
	bound = git_deflate_bound(&stream, size);
	deflated = xmalloc(bound);
	stream.next_out = deflated;
	stream.avail_out = bound;

	stream.next_in = (unsigned char *)data;
	stream.avail_in = size;
	while (git_deflate(&stream, Z_FINISH) == Z_OK)
		; /* nothing */
	git_deflate_end(&stream);
	*result_size = stream.total_out;
	return deflated;
}