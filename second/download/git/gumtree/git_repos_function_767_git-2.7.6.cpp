static inline int standard_header_field(const char *field, size_t len)
{
	return ((len == 4 && !memcmp(field, "tree ", 5)) ||
		(len == 6 && !memcmp(field, "parent ", 7)) ||
		(len == 6 && !memcmp(field, "author ", 7)) ||
		(len == 9 && !memcmp(field, "committer ", 10)) ||
		(len == 8 && !memcmp(field, "encoding ", 9)));
}