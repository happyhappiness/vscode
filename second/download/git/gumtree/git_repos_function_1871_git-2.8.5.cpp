int hash_sha1_file_literally(const void *buf, unsigned long len, const char *type,
			     unsigned char *sha1, unsigned flags)
{
	char *header;
	int hdrlen, status = 0;

	/* type string, SP, %lu of the length plus NUL must fit this */
	hdrlen = strlen(type) + 32;
	header = xmalloc(hdrlen);
	write_sha1_file_prepare(buf, len, type, sha1, header, &hdrlen);

	if (!(flags & HASH_WRITE_OBJECT))
		goto cleanup;
	if (freshen_packed_object(sha1) || freshen_loose_object(sha1))
		goto cleanup;
	status = write_loose_object(sha1, header, hdrlen, buf, len, 0);

cleanup:
	free(header);
	return status;
}