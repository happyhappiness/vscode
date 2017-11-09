static struct passwd *want_all_groups(int f_out, uid_t uid)
{
	struct passwd *pw;
	gid_t *gid_p;
	if ((pw = getpwuid(uid)) == NULL) {
		rsyserr(FLOG, errno, "getpwuid failed");
		io_printf(f_out, "@ERROR: getpwuid failed\n");
		return NULL;
	}
	/* Start with the default group and initgroups() will add the rest. */
	gid_p = EXPAND_ITEM_LIST(&gid_list, gid_t, -32);
	*gid_p = pw->pw_gid;
	return pw;
}