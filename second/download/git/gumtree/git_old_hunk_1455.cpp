
int is_builtin(const char *s)
{
	return !!get_builtin(s);
}

#ifdef STRIP_EXTENSION
static void strip_extension(const char **argv)
{
	size_t len;

	if (strip_suffix(argv[0], STRIP_EXTENSION, &len))
