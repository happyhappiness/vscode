int same_encoding(const char *src, const char *dst)
{
	if (is_encoding_utf8(src) && is_encoding_utf8(dst))
		return 1;
	return !strcasecmp(src, dst);
}