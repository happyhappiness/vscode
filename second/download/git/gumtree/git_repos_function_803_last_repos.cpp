static int stream_blocked(const unsigned char *sha1)
{
	struct git_istream *st;
	enum object_type type;
	unsigned long sz;
	char buf[BLOCKSIZE];
	ssize_t readlen;

	st = open_istream(sha1, &type, &sz, NULL);
	if (!st)
		return error("cannot stream blob %s", sha1_to_hex(sha1));
	for (;;) {
		readlen = read_istream(st, buf, sizeof(buf));
		if (readlen <= 0)
			break;
		do_write_blocked(buf, readlen);
	}
	close_istream(st);
	if (!readlen)
		finish_record();
	return readlen;
}