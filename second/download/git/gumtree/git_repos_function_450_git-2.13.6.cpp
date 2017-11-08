static struct diff_rename_dst *locate_rename_dst(struct diff_filespec *two)
{
	int ofs = find_rename_dst(two);
	return ofs < 0 ? NULL : &rename_dst[ofs];
}