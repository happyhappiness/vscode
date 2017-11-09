static inline int has_sha1_file(const unsigned char *sha1)
{
	return has_sha1_file_with_flags(sha1, 0);
}