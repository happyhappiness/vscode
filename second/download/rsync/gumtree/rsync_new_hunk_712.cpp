	if (flist->count < 2)
		return;

	if (hlink_list)
		free(hlink_list);

	if (!(hlink_list = new_array(struct file_struct *, flist->count)))
		out_of_memory("init_hard_links");

	hlink_count = 0;
	for (i = 0; i < flist->count; i++) {
		if (flist->files[i]->link_u.idev)
			hlink_list[hlink_count++] = flist->files[i];
	}

	qsort(hlink_list, hlink_count,
	    sizeof hlink_list[0], (int (*)()) hlink_compare);

	if (!hlink_count) {
		free(hlink_list);
		hlink_list = NULL;
	} else
		link_idev_data(flist);
#endif
}

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

#if SUPPORT_HARD_LINKS
static void hard_link_one(char *hlink1, char *hlink2)
{
	if (do_link(hlink1, hlink2)) {
		if (verbose) {
			rprintf(FINFO, "link %s => %s failed: %s\n",
			    hlink2, hlink1, strerror(errno));
		}
	}
	else if (verbose)
		rprintf(FINFO, "%s => %s\n", hlink2, hlink1);
}
#endif



/**
 * Create any hard links in the global hlink_list.  They were put
 * there by running init_hard_links on the filelist.
 **/
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
