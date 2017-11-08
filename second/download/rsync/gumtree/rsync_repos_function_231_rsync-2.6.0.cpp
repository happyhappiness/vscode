static int is_in_group(gid_t gid)
{
#ifdef GETGROUPS_T
	static gid_t last_in = (gid_t) -2, last_out;
	static int ngroups = -2;
	static GETGROUPS_T *gidset;
	int n;

	if (gid == last_in)
		return last_out;
	if (ngroups < -1) {
		/* treat failure (-1) as if not member of any group */
		ngroups = getgroups(0, 0);
		if (ngroups > 0) {
			gidset = new_array(GETGROUPS_T, ngroups);
			ngroups = getgroups(ngroups, gidset);
		}
	}

	last_in = gid;
	last_out = 0;
	for (n = 0; n < ngroups; n++) {
		if (gidset[n] == gid) {
			last_out = 1;
			break;
		}
	}
	return last_out;

#else
	return 0;
#endif
}