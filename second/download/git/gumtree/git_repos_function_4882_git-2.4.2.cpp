static int get_remote_group(const char *key, const char *value, void *priv)
{
	struct remote_group_data *g = priv;

	if (starts_with(key, "remotes.") &&
			!strcmp(key + 8, g->name)) {
		/* split list by white space */
		int space = strcspn(value, " \t\n");
		while (*value) {
			if (space > 1) {
				string_list_append(g->list,
						   xstrndup(value, space));
			}
			value += space + (value[space] != '\0');
			space = strcspn(value, " \t\n");
		}
	}

	return 0;
}