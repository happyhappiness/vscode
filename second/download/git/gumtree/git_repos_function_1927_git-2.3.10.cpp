static const struct string_list *protocol_whitelist(void)
{
	static int enabled = -1;
	static struct string_list allowed = STRING_LIST_INIT_DUP;

	if (enabled < 0) {
		const char *v = getenv("GIT_ALLOW_PROTOCOL");
		if (v) {
			string_list_split(&allowed, v, ':', -1);
			string_list_sort(&allowed);
			enabled = 1;
		} else {
			enabled = 0;
		}
	}

	return enabled ? &allowed : NULL;
}