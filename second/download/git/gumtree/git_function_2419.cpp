static void *unpack_data(struct object_entry *obj,
			 int (*consume)(const unsigned char *, unsigned long, void *),
			 void *cb_data)
{
	off_t from = obj[0].idx.offset + obj[0].hdr_size;
	unsigned long len = obj[1].idx.offset - from;
	unsigned char *data, *inbuf;
	git_zstream stream;
	int status;

	data = xmallocz(consume ? 64*1024 : obj->size);
	inbuf = xmalloc((len < 64*1024) ? len : 64*1024);

	memset(&stream, 0, sizeof(stream));
	git_inflate_init(&stream);
	stream.next_out = data;
	stream.avail_out = consume ? 64*1024 : obj->size;

	do {
		ssize_t n = (len < 64*1024) ? len : 64*1024;
		n = xpread(get_thread_data()->pack_fd, inbuf, n, from);
		if (n < 0)
			die_errno(_("cannot pread pack file"));
		if (!n)
			die(Q_("premature end of pack file, %lu byte missing",
			       "premature end of pack file, %lu bytes missing",
			       len),
			    len);
		from += n;
		len -= n;
		stream.next_in = inbuf;
		stream.avail_in = n;
		if (!consume)
			status = git_inflate(&stream, 0);
		else {
			do {
				status = git_inflate(&stream, 0);
				if (consume(data, stream.next_out - data, cb_data)) {
					free(inbuf);
					free(data);
					return NULL;
				}
				stream.next_out = data;
				stream.avail_out = 64*1024;
			} while (status == Z_OK && stream.avail_in);
		}
	} while (len && status == Z_OK && !stream.avail_in);

	/* This has been inflated OK when first encountered, so... */
	if (status != Z_STREAM_END || stream.total_out != obj->size)
		die(_("serious inflate inconsistency"));

	git_inflate_end(&stream);
	free(inbuf);
	if (consume) {
		free(data);
		data = NULL;
	}
	return data;
}