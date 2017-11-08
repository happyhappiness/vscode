int hard_link_check(struct file_struct *file, int skip)
{
	if (!hlink_list || !file->link_u.links)
		return 0;
	if (skip && !(file->flags & FLAG_HLINK_EOL))
		hlink_list[file->F_HLINDEX] = file->F_NEXT;
	if (hlink_list[file->F_HLINDEX] != file) {
		if (verbose > 1) {
			rprintf(FINFO, "\"%s\" is a hard link\n",
			    f_name(file));
		}
		return 1;
	}
	return 0;
}