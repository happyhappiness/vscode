static int add_a_group(int f_out, const char *gname)
{
	gid_t gid, *gid_p;
	if (!group_to_gid(gname, &gid, True)) {
		rprintf(FLOG, "Invalid gid %s\n", gname);
		io_printf(f_out, "@ERROR: invalid gid %s\n", gname);
		return -1;
	}
	gid_p = EXPAND_ITEM_LIST(&gid_list, gid_t, -32);
	*gid_p = gid;
	return 0;
}