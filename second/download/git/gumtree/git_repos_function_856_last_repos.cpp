static inline const char *has_glob_specials(const char *pattern)
{
	return strpbrk(pattern, "?*[");
}