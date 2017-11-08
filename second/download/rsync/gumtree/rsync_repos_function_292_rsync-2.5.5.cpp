static int check_exclude_file(int f, char *fname, STRUCT_STAT * st)
{
	extern int delete_excluded;

	/* f is set to -1 when calculating deletion file list */
	if ((f == -1) && delete_excluded) {
		return 0;
	}
	if (check_exclude(fname, local_exclude_list, st)) {
		return 1;
	}
	return 0;
}