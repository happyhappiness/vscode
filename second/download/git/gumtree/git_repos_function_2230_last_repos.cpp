int check_sha1_signature(const unsigned char *sha1, void *map,
			 unsigned long size, const char *type)
{
	unsigned char real_sha1[20];
	enum object_type obj_type;
	struct git_istream *st;
	git_SHA_CTX c;
	char hdr[32];
	int hdrlen;

	if (map) {
		hash_sha1_file(map, size, type, real_sha1);
		return hashcmp(sha1, real_sha1) ? -1 : 0;
	}

	st = open_istream(sha1, &obj_type, &size, NULL);
	if (!st)
		return -1;

	/* Generate the header */
	hdrlen = xsnprintf(hdr, sizeof(hdr), "%s %lu", typename(obj_type), size) + 1;

	/* Sha1.. */
	git_SHA1_Init(&c);
	git_SHA1_Update(&c, hdr, hdrlen);
	for (;;) {
		char buf[1024 * 16];
		ssize_t readlen = read_istream(st, buf, sizeof(buf));

		if (readlen < 0) {
			close_istream(st);
			return -1;
		}
		if (!readlen)
			break;
		git_SHA1_Update(&c, buf, readlen);
	}
	git_SHA1_Final(real_sha1, &c);
	close_istream(st);
	return hashcmp(sha1, real_sha1) ? -1 : 0;
}