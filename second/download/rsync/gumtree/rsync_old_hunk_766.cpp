
static int access_match(char *list, char *addr, char *host)
{
	char *tok;
	char *list2 = strdup(list);

	if (!list2) out_of_memory("access_match");

	strlower(list2);
	if (host) strlower(host);

	for (tok=strtok(list2," ,\t"); tok; tok=strtok(NULL," ,\t")) {
		if (match_hostname(host, tok) || match_address(addr, tok)) {
			free(list2);
			return 1;
		}
	}

	free(list2);
	return 0;
}

int allow_access(char *addr, char *host, char *allow_list, char *deny_list)
{
	/* if theres no deny list and no allow list then allow access */
	if ((!deny_list || !*deny_list) && (!allow_list || !*allow_list))
		return 1;

	/* if there is an allow list but no deny list then allow only hosts
	   on the allow list */
	if (!deny_list || !*deny_list)
		return(access_match(allow_list, addr, host));

	/* if theres a deny list but no allow list then allow
	   all hosts not on the deny list */
	if (!allow_list || !*allow_list)
		return(!access_match(deny_list,addr,host));

	/* if there are both type of list then allow all hosts on the
           allow list */
	if (access_match(allow_list,addr,host))
		return 1;

	/* if there are both type of list and it's not on the allow then
	   allow it if its not on the deny */
	if (access_match(deny_list,addr,host))
		return 0;

	return 1;
}
