static int get_remote_default(const char *key, const char *value, void *priv)
{
	if (strcmp(key, "remotes.default") == 0) {
		int *found = priv;
		*found = 1;
	}
	return 0;
}