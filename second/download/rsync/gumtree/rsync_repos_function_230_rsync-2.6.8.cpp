int hard_link_check(struct file_struct *file, int ndx, char *fname,
		    int statret, STRUCT_STAT *st, int itemizing,
		    enum logcode code, int skip)
{
#ifdef SUPPORT_HARD_LINKS
	int head;
	if (skip && !(file->flags & FLAG_HLINK_EOL))
		head = hlink_list[file->F_HLINDEX] = file->F_NEXT;
	else
		head = hlink_list[file->F_HLINDEX];
	if (ndx != head) {
		struct file_struct *head_file = FPTR(head);
		if (!log_format_has_i && verbose > 1) {
			rprintf(FINFO, "\"%s\" is a hard link\n",
				f_name(file, NULL));
		}
		if (head_file->F_HLINDEX == FINISHED_LINK) {
			STRUCT_STAT st2, st3;
			char *toname = f_name(head_file, NULL);
			if (link_stat(toname, &st2, 0) < 0) {
				rsyserr(FERROR, errno, "stat %s failed",
					full_fname(toname));
				return -1;
			}
			if (statret < 0 && basis_dir[0] != NULL) {
				char cmpbuf[MAXPATHLEN];
				int j = 0;
				do {
					pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
					if (link_stat(cmpbuf, &st3, 0) < 0)
						continue;
					if (link_dest) {
						if (st2.st_dev != st3.st_dev
						 || st2.st_ino != st3.st_ino)
							continue;
						statret = 1;
						st = &st3;
						if (verbose < 2 || !log_format_has_i)
							itemizing = code = 0;
						break;
					}
					if (!unchanged_file(cmpbuf, file, &st3))
						continue;
					statret = 1;
					st = &st3;
					if (unchanged_attrs(file, &st3))
						break;
				} while (basis_dir[++j] != NULL);
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