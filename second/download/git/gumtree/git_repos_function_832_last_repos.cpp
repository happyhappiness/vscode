int is_utf8_locale(void)
{
#ifdef NO_GETTEXT
	if (!charset) {
		const char *env = getenv("LC_ALL");
		if (!env || !*env)
			env = getenv("LC_CTYPE");
		if (!env || !*env)
			env = getenv("LANG");
		if (!env)
			env = "";
		if (strchr(env, '.'))
			env = strchr(env, '.') + 1;
		charset = xstrdup(env);
	}
#endif
	return is_encoding_utf8(charset);
}