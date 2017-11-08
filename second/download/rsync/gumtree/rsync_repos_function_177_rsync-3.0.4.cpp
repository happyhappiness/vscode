static int access_match(char *list, char *addr, char *host)
{
	char *tok;
	char *list2 = strdup(list);

	if (!list2)
		out_of_memory("access_match");

	strlower(list2);
	if (host)
		strlower(host);

	for (tok = strtok(list2, " ,\t"); tok; tok = strtok(NULL, " ,\t")) {
		if (match_hostname(host, tok) || match_address(addr, tok)) {
			free(list2);
			return 1;
		}
	}

	free(list2);
	return 0;
}