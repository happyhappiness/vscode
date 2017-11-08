void hard_link_cluster(struct file_struct *file, int master, int itemizing,
		       enum logcode code)
{
#ifdef SUPPORT_HARD_LINKS
	char hlink1[MAXPATHLEN];
	char *hlink2;
	STRUCT_STAT st1, st2;
	int statret, ndx = master;

	file->F_HLINDEX = FINISHED_LINK;
	if (link_stat(f_name(file, hlink1), &st1, 0) < 0)
		return;
	if (!(file->flags & FLAG_HLINK_TOL)) {
		while (!(file->flags & FLAG_HLINK_EOL)) {
			ndx = file->F_NEXT;
			file = FPTR(ndx);
		}
	}
	do {
		ndx = file->F_NEXT;
		file = FPTR(ndx);
		if (file->F_HLINDEX != SKIPPED_LINK)
			continue;
		hlink2 = f_name(file, NULL);
		statret = link_stat(hlink2, &st2, 0);
		maybe_hard_link(file, ndx, hlink2, statret, &st2,
				hlink1, &st1, itemizing, code);
		file->F_HLINDEX = FINISHED_LINK;
	} while (!(file->flags & FLAG_HLINK_EOL));
#endif
}