static int filter_server_path(char *arg)
{
	char *s;

	if (server_filter_list.head) {
		for (s = arg; (s = strchr(s, '/')) != NULL; ) {
			*s = '\0';
			if (check_filter(&server_filter_list, arg, 1) < 0) {
				/* We must leave arg truncated! */
				return 1;
			}
			*s++ = '/';
		}
	}
	return 0;
}