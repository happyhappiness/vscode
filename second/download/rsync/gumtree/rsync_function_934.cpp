static inline void string_set(char **s, const char *v)
{
	if (!v)
		*s = NULL;
	else if (!(*s = strdup(v)))
		out_of_memory("string_set");
}