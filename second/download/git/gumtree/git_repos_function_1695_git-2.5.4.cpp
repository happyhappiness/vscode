int hash_sha1_file(const void *buf, unsigned long len, const char *type,
                   unsigned char *sha1)
{
	char hdr[32];
	int hdrlen;
	write_sha1_file_prepare(buf, len, type, sha1, hdr, &hdrlen);
	return 0;
}