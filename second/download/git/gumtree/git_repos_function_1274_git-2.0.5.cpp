static inline const char *skip_prefix(const char *str, const char *prefix)
{
	do {
		if (!*prefix)
			return str;
	} while (*str++ == *prefix++);
	return NULL;
}