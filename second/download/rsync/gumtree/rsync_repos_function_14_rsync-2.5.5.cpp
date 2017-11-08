static void string_set(char **s, const char *v)
{
	if (!v) {
		*s = NULL;
		return;
	}
	*s = strdup(v);
	if (!*s)
		exit_cleanup(RERR_MALLOC);
}