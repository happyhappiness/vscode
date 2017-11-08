static inline int would_convert_to_git(const char *path, const char *src,
				       size_t len, enum safe_crlf checksafe)
{
	return convert_to_git(path, src, len, NULL, checksafe);
}