static char *get_header(const char *msg, const char *key)
{
	size_t len;
	const char *v = find_commit_header(msg, key, &len);
	return v ? xmemdupz(v, len) : NULL;
}