static int want_all_groups(int f_out, uid_t uid)
{
	const char *err;
	gid_count = MAX_GID_LIST;
	if ((err = getallgroups(uid, gid_list, &gid_count)) != NULL) {
		rsyserr(FLOG, errno, "%s", err);
		io_printf(f_out, "@ERROR: %s\n", err);
		return -1;
	}
	return 0;
}