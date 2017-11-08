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
		if (!stdout_format_has_i && verbose > 1) {
			rprintf(FINFO, "\"%s\" is a hard link\n",
				f_name(file, NULL));
		}
		if (head_file->F_HLINDEX == FINISHED_LINK) {
			STRUCT_STAT st2, st3;
			char toname[MAXPATHLEN];
			int ldu = head_file->link_u.links->link_dest_used;
			if (ldu) {
				pathjoin(toname, MAXPATHLEN, basis_dir[ldu-1],
					 f_name(head_file, NULL));
			} else
				f_name(head_file, toname);
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
						if (verbose < 2 || !stdout_format_has_i) {
							itemizing = 0;
							code = FNONE;
						}
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
			if (remove_source_files == 1 && do_xfers) {
				char numbuf[4];
				SIVAL(numbuf, 0, ndx);
				send_msg(MSG_SUCCESS, numbuf, 4);
			}
			file->F_HLINDEX = FINISHED_LINK;
		} else
			file->F_HLINDEX = SKIPPED_LINK;
		return 1;
	}
#endif
	return 0;
}