static void *unpack_entry_data(off_t offset, unsigned long size,
			       enum object_type type, unsigned char *sha1)
{
	static char fixed_buf[8192];
	int status;
	git_zstream stream;
	void *buf;
	git_SHA_CTX c;
	char hdr[32];
	int hdrlen;

	if (!is_delta_type(type)) {
		hdrlen = xsnprintf(hdr, sizeof(hdr), "%s %lu", typename(type), size) + 1;
		git_SHA1_Init(&c);
		git_SHA1_Update(&c, hdr, hdrlen);
	} else
		sha1 = NULL;
	if (type == OBJ_BLOB && size > big_file_threshold)
		buf = fixed_buf;
	else
		buf = xmallocz(size);

	memset(&stream, 0, sizeof(stream));
	git_inflate_init(&stream);
	stream.next_out = buf;
	stream.avail_out = buf == fixed_buf ? sizeof(fixed_buf) : size;

	do {
		unsigned char *last_out = stream.next_out;
		stream.next_in = fill(1);
		stream.avail_in = input_len;
		status = git_inflate(&stream, 0);
		use(input_len - stream.avail_in);
		if (sha1)
			git_SHA1_Update(&c, last_out, stream.next_out - last_out);
		if (buf == fixed_buf) {
			stream.next_out = buf;
			stream.avail_out = sizeof(fixed_buf);
		}
	} while (status == Z_OK);
	if (stream.total_out != size || status != Z_STREAM_END)
		bad_object(offset, _("inflate returned %d"), status);
	git_inflate_end(&stream);
	if (sha1)
		git_SHA1_Final(sha1, &c);
	return buf == fixed_buf ? NULL : buf;
}