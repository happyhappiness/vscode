  out:
	freeaddrinfo(resa);
	freeaddrinfo(rest);
	return ret;
}

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

int allow_access(const char *addr, const char **host_ptr, int i)
{
	const char *allow_list = lp_hosts_allow(i);
	const char *deny_list = lp_hosts_deny(i);

	if (allow_list && !*allow_list)
		allow_list = NULL;
	if (deny_list && !*deny_list)
		deny_list = NULL;

	allow_forward_dns = lp_forward_lookup(i);

	/* If we match an allow-list item, we always allow access. */
	if (allow_list) {
		if (access_match(allow_list, addr, host_ptr))
			return 1;
		/* For an allow-list w/o a deny-list, disallow non-matches. */
		if (!deny_list)
			return 0;
	}

	/* If we match a deny-list item (and got past any allow-list
	 * items), we always disallow access. */
	if (deny_list && access_match(deny_list, addr, host_ptr))
		return 0;

	/* Allow all other access. */
	return 1;
}
