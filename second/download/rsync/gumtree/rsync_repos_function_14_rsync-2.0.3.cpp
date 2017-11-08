static void string_set(char **s, char *v)
{
	if (!v) {
		*s = NULL;
		return;
	}
	*s = strdup(v);
	if (!*s) exit_cleanup(1);
}