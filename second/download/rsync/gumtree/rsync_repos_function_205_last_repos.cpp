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