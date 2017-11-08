static void var_override(const char **var, char *value)
{
	if (value) {
		free((void *)*var);
		*var = xstrdup(value);
	}
}