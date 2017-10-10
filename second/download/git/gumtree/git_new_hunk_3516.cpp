
static void *unpack_data(struct object_entry *obj,
			 int (*consume)(const unsigned char *, unsigned long, void *),
			 void *cb_data)
{
	off_t from = obj[0].idx.offset + obj[0].hdr_size;
	off_t len = obj[1].idx.offset - from;
	unsigned char *data, *inbuf;
	git_zstream stream;
	int status;

	data = xmallocz(consume ? 64*1024 : obj->size);
	inbuf = xmalloc((len < 64*1024) ? (int)len : 64*1024);

	memset(&stream, 0, sizeof(stream));
	git_inflate_init(&stream);
	stream.next_out = data;
	stream.avail_out = consume ? 64*1024 : obj->size;

	do {
		ssize_t n = (len < 64*1024) ? (ssize_t)len : 64*1024;
		n = xpread(get_thread_data()->pack_fd, inbuf, n, from);
		if (n < 0)
			die_errno(_("cannot pread pack file"));
		if (!n)
			die(Q_("premature end of pack file, %"PRIuMAX" byte missing",
			       "premature end of pack file, %"PRIuMAX" bytes missing",
			       (unsigned int)len),
			    (uintmax_t)len);
		from += n;
		len -= n;
		stream.next_in = inbuf;
		stream.avail_in = n;
		if (!consume)
			status = git_inflate(&stream, 0);
