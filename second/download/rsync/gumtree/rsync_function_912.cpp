static int add_a_group(int f_out, const char *gname)
{
	gid_t gid;
	if (!group_to_gid(gname, &gid, True)) {
		rprintf(FLOG, "Invalid gid %s\n", gname);
		io_printf(f_out, "@ERROR: invalid gid %s\n", gname);
		return -1;
	}
	if (gid_count == MAX_GID_LIST) {
		rprintf(FLOG, "Too many groups specified via gid parameter.\n");
		io_printf(f_out, "@ERROR: too many groups\n");
		return -1;
	}
	gid_list[gid_count++] = gid;
	return 0;
}