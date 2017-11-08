void delete_files(struct file_list *flist)
{
	struct file_list *local_file_list;
	int i, j;
	char *argv[1], fbuf[MAXPATHLEN];
	static int deletion_count;

	if (cvs_exclude)
		add_cvs_excludes();

	if (io_error && !(lp_ignore_errors(module_id) || ignore_errors)) {
		rprintf(FINFO,"IO error encountered - skipping file deletion\n");
		return;
	}

	for (j = 0; j < flist->count; j++) {
		if (!(flist->files[j]->flags & FLAG_TOP_DIR)
		    || !S_ISDIR(flist->files[j]->mode))
			continue;

		argv[0] = f_name_to(flist->files[j], fbuf);

		if (!(local_file_list = send_file_list(-1, 1, argv)))
			continue;

		if (verbose > 1)
			rprintf(FINFO, "deleting in %s\n", fbuf);

		for (i = local_file_list->count-1; i >= 0; i--) {
			if (max_delete && deletion_count > max_delete)
				break;
			if (!local_file_list->files[i]->basename)
				continue;
			if (flist_find(flist,local_file_list->files[i]) < 0) {
				char *f = f_name(local_file_list->files[i]);
				if (make_backups && (backup_dir || !is_backup_file(f))) {
					(void) make_backup(f);
					if (verbose)
						rprintf(FINFO, "deleting %s\n", f);
				} else {
					int mode = local_file_list->files[i]->mode;
					delete_one(f, S_ISDIR(mode) != 0);
				}
				deletion_count++;
			}
		}
		flist_free(local_file_list);
	}
}