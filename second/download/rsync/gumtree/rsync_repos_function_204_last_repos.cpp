static int access_match(const char *list, const char *addr, const char **host_ptr)
{
	char *tok;
	char *list2 = strdup(list);

	if (!list2)
		out_of_memory("access_match");

	strlower(list2);

	for (tok = strtok(list2, " ,\t"); tok; tok = strtok(NULL, " ,\t")) {
		if (match_hostname(host_ptr, addr, tok) || match_address(addr, tok)) {
			free(list2);
			return 1;
		}
	}

	free(list2);
	return 0;
}