static inline int is_empty_tree_sha1(const unsigned char *sha1)
{
	return !hashcmp(sha1, EMPTY_TREE_SHA1_BIN);
}