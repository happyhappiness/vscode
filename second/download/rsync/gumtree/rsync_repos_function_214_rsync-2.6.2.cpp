static int exclude_server_path(char *arg)
{
	char *s;

	if (server_exclude_list.head) {
		for (s = arg; (s = strchr(s, '/')) != NULL; ) {
			*s = '\0';
			if (check_exclude(&server_exclude_list, arg, 1) < 0) {
				/* We must leave arg truncated! */
				return 1;
			}
			*s++ = '/';
		}
	}
	return 0;
}