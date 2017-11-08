int hard_link_check(struct file_struct *file, int ndx, char *fname,
		    int statret, STRUCT_STAT *st, int itemizing,
		    enum logcode code, int skip)
{
#ifdef SUPPORT_HARD_LINKS
	int head;
	if (!file->link_u.links)
		return 0;
	if (skip && !(file->flags & FLAG_HLINK_EOL))
		head = hlink_list[file->F_HLINDEX] = file->F_NEXT;
	else
		head = hlink_list[file->F_HLINDEX];
	if (ndx != head) {
		struct file_struct *head_file = FPTR(head);
		if (!log_format_has_i && verbose > 1) {
			rprintf(FINFO, "\"%s\" is a hard link\n",
				safe_fname(f_name(file)));
		}
		if (head_file->F_HLINDEX == FINISHED_LINK) {
			STRUCT_STAT st2;
			char *toname = f_name(head_file);
			if (link_stat(toname, &st2, 0) < 0) {
				rsyserr(FERROR, errno, "stat %s failed",
					full_fname(toname));
				return -1;
			}
			maybe_hard_link(file, ndx, fname, statret, st,
					toname, &st2, itemizing, code);
			file->F_HLINDEX = FINISHED_LINK;
		} else
			file->F_HLINDEX = SKIPPED_LINK;
		return 1;
	}
#endif
	return 0;
}