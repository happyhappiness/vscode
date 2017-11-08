static void *unpack_compressed_entry(struct packed_git *p,
				    struct pack_window **w_curs,
				    off_t curpos,
				    unsigned long size)
{
	int st;
	git_zstream stream;
	unsigned char *buffer, *in;

	buffer = xmallocz_gently(size);
	if (!buffer)
		return NULL;
	memset(&stream, 0, sizeof(stream));
	stream.next_out = buffer;
	stream.avail_out = size + 1;

	git_inflate_init(&stream);
	do {
		in = use_pack(p, w_curs, curpos, &stream.avail_in);
		stream.next_in = in;
		st = git_inflate(&stream, Z_FINISH);
		if (!stream.avail_out)
			break; /* the payload is larger than it should be */
		curpos += stream.next_in - in;
	} while (st == Z_OK || st == Z_BUF_ERROR);
	git_inflate_end(&stream);
	if ((st != Z_STREAM_END) || stream.total_out != size) {
		free(buffer);
		return NULL;
	}

	return buffer;
}