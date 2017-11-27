static int check_ignore_if (const char *interface)
{
	int i;

	/* If no interfaces are given collect all interfaces. Mostly to be
	 * backwards compatible, but also because this is much easier. */
	if (if_list_num < 1)
		return (0);

	for (i = 0; i < if_list_num; i++)
		if (strcasecmp (interface, if_list[i]) == 0)
			return (if_list_action);
	return (1 - if_list_action);
}