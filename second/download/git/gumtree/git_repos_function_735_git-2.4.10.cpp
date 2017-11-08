static inline int is_empty_blob_sha1(const unsigned char *sha1)
{
	return !hashcmp(sha1, EMPTY_BLOB_SHA1_BIN);
}