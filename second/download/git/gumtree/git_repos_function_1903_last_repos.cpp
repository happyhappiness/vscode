const char *get_super_prefix(void)
{
	static int initialized;
	if (!initialized) {
		super_prefix = getenv(GIT_SUPER_PREFIX_ENVIRONMENT);
		initialized = 1;
	}
	return super_prefix;
}