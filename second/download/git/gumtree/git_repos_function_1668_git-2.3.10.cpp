int write_sha1_file(const void *buf, unsigned long len, const char *type, unsigned char *returnsha1)
{
	unsigned char sha1[20];
	char hdr[32];
	int hdrlen;

	/* Normally if we have it in the pack then we do not bother writing
	 * it out into .git/objects/??/?{38} file.
	 */
	write_sha1_file_prepare(buf, len, type, sha1, hdr, &hdrlen);
	if (returnsha1)
		hashcpy(returnsha1, sha1);
	if (freshen_loose_object(sha1) || freshen_packed_object(sha1))
		return 0;
	return write_loose_object(sha1, hdr, hdrlen, buf, len, 0);
}