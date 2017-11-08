static int write_compressed(struct sha1file *f, void *in, unsigned int size)
{
	git_zstream stream;
	int status;
	unsigned char outbuf[4096];

	git_deflate_init(&stream, zlib_compression_level);
	stream.next_in = in;
	stream.avail_in = size;

	do {
		stream.next_out = outbuf;
		stream.avail_out = sizeof(outbuf);
		status = git_deflate(&stream, Z_FINISH);
		sha1write(f, outbuf, sizeof(outbuf) - stream.avail_out);
	} while (status == Z_OK);

	if (status != Z_STREAM_END)
		die(_("unable to deflate appended object (%d)"), status);
	size = stream.total_out;
	git_deflate_end(&stream);
	return size;
}