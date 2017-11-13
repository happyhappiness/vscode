static int check_stream_sha1(git_zstream *stream,
			     const char *hdr,
			     unsigned long size,
			     const char *path,
			     const unsigned char *expected_sha1)
{
	git_SHA_CTX c;
	unsigned char real_sha1[GIT_SHA1_RAWSZ];
	unsigned char buf[4096];
	unsigned long total_read;
	int status = Z_OK;

	git_SHA1_Init(&c);
	git_SHA1_Update(&c, hdr, stream->total_out);

	/*
	 * We already read some bytes into hdr, but the ones up to the NUL
	 * do not count against the object's content size.
	 */
	total_read = stream->total_out - strlen(hdr) - 1;

	/*
	 * This size comparison must be "<=" to read the final zlib packets;
	 * see the comment in unpack_sha1_rest for details.
	 */
	while (total_read <= size &&
	       (status == Z_OK || status == Z_BUF_ERROR)) {
		stream->next_out = buf;
		stream->avail_out = sizeof(buf);
		if (size - total_read < stream->avail_out)
			stream->avail_out = size - total_read;
		status = git_inflate(stream, Z_FINISH);
		git_SHA1_Update(&c, buf, stream->next_out - buf);
		total_read += stream->next_out - buf;
	}
	git_inflate_end(stream);

	if (status != Z_STREAM_END) {
		error("corrupt loose object '%s'", sha1_to_hex(expected_sha1));
		return -1;
	}
	if (stream->avail_in) {
		error("garbage at end of loose object '%s'",
		      sha1_to_hex(expected_sha1));
		return -1;
	}

	git_SHA1_Final(real_sha1, &c);
	if (hashcmp(expected_sha1, real_sha1)) {
		error("sha1 mismatch for %s (expected %s)", path,
		      sha1_to_hex(expected_sha1));
		return -1;
	}

	return 0;
}