static int try_dests_non(struct file_struct *file, char *fname, int ndx,
			 int itemizing, int *possible_ptr,
			 int maybe_ATTRS_REPORT, enum logcode code)
{
	char fnamebuf[MAXPATHLEN], lnk[MAXPATHLEN];
	STRUCT_STAT st;
	int len, i = 0;

	do {
		pathjoin(fnamebuf, MAXPATHLEN, basis_dir[i], fname);
		if (link_stat(fnamebuf, &st, 0) < 0 || S_ISDIR(st.st_mode)
		 || !unchanged_attrs(file, &st))
			continue;
		if (S_ISLNK(file->mode)) {
#ifdef SUPPORT_LINKS
			if ((len = readlink(fnamebuf, lnk, MAXPATHLEN-1)) <= 0)
				continue;
			lnk[len] = '\0';
			if (strcmp(lnk, file->u.link) != 0)
#endif
				continue;
		} else {
			if (!IS_DEVICE(st.st_mode) || st.st_rdev != file->u.rdev)
				continue;
		}
		if (link_dest) {
			if (do_link(fnamebuf, fname) < 0) {
				/* TODO improve this to be based on errno? */
				*possible_ptr = 0;
				break;
			}
			if (preserve_hard_links && file->link_u.links)
				hard_link_cluster(file, ndx, itemizing, code);
		}
		if (itemizing && log_format_has_i && verbose > 1) {
			int changes = compare_dest ? 0 : ITEM_LOCAL_CHANGE
				    + (link_dest ? ITEM_XNAME_FOLLOWS : 0);
			char *lp = link_dest ? "" : NULL;
			itemize(file, ndx, 0, &st, changes, 0, lp);
		}
		if (verbose > 1 && maybe_ATTRS_REPORT) {
			code = daemon_log_format_has_i || dry_run
			     ? FCLIENT : FINFO;
			rprintf(code, "%s is uptodate\n", fname);
		}
		return -2;
	} while (basis_dir[++i] != NULL);

	return -1;
}