void do_hard_links(void)
{
#if SUPPORT_HARD_LINKS
	struct file_struct *file, *first;
	char hlink1[MAXPATHLEN];
	char *hlink2;
	STRUCT_STAT st1, st2;
	int i;

	if (!hlink_list)
		return;

	for (i = 0; i < hlink_count; i++) {
		first = file = hlink_list[i];
		if (link_stat(f_name_to(first, hlink1), &st1) != 0)
			continue;
		while ((file = file->F_NEXT) != first) {
			hlink2 = f_name(file);
			if (link_stat(hlink2, &st2) == 0) {
				if (st2.st_dev == st1.st_dev
				    && st2.st_ino == st1.st_ino)
					continue;
				if (make_backups) {
					if (!make_backup(hlink2))
						continue;
				} else if (robust_unlink(hlink2)) {
					if (verbose > 0) {
						rprintf(FINFO,
						    "unlink %s failed: %s\n",
						    full_fname(hlink2), 
						    strerror(errno));
					}
					continue;
				}
			}
			hard_link_one(hlink1, hlink2);
		}
	}
#endif
}