static int is_in_group(gid_t gid)
{
#ifdef HAVE_GETGROUPS
	static gid_t last_in = GID_NONE, last_out;
	static int ngroups = -2;
	static GETGROUPS_T *gidset;
	int n;

	if (gid == last_in)
		return last_out;
	if (ngroups < -1) {
		gid_t mygid = MY_GID();
		if ((ngroups = getgroups(0, NULL)) < 0)
			ngroups = 0;
		gidset = new_array(GETGROUPS_T, ngroups+1);
		if (!gidset)
			out_of_memory("is_in_group");
		if (ngroups > 0)
			ngroups = getgroups(ngroups, gidset);
		/* The default gid might not be in the list on some systems. */
		for (n = 0; n < ngroups; n++) {
			if (gidset[n] == mygid)
				break;
		}
		if (n == ngroups)
			gidset[ngroups++] = mygid;
		if (verbose > 3) {
			int pos;
			char *gidbuf = new_array(char, ngroups*21+32);
			if (!gidbuf)
				out_of_memory("is_in_group");
			sprintf(gidbuf, "process has %d gid%s: ",
			    ngroups, ngroups == 1? "" : "s");
			pos = strlen(gidbuf);
			for (n = 0; n < ngroups; n++) {
				sprintf(gidbuf+pos, " %d", (int)gidset[n]);
				pos += strlen(gidbuf+pos);
			}
			rprintf(FINFO, "%s\n", gidbuf);
			free(gidbuf);
		}
	}

	last_in = gid;
	for (n = 0; n < ngroups; n++) {
		if (gidset[n] == gid)
			return last_out = 1;
	}
	return last_out = 0;

#else
	static gid_t mygid = GID_NONE;
	if (mygid == GID_NONE) {
		mygid = MY_GID();
		if (verbose > 3)
			rprintf(FINFO, "process has gid %d\n", (int)mygid);
	}
	return gid == mygid;
#endif
}