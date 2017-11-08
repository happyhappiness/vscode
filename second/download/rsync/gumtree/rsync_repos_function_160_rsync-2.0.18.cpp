static void delete_files(struct file_list *flist)
{
	struct file_list *local_file_list;
	int i, j;
	char *name;

	if (cvs_exclude)
		add_cvs_excludes();

	if (io_error) {
		rprintf(FINFO,"IO error encountered - skipping file deletion\n");
		return;
	}

	for (j=0;j<flist->count;j++) {
		if (!S_ISDIR(flist->files[j]->mode) || 
		    !(flist->files[j]->flags & FLAG_DELETE)) continue;

		if (remote_version < 19 &&
		    delete_already_done(flist, j)) continue;

		name = strdup(f_name(flist->files[j]));

		if (!(local_file_list = send_file_list(-1,1,&name))) {
			free(name);
			continue;
		}

		if (verbose > 1)
			rprintf(FINFO,"deleting in %s\n", name);

		for (i=local_file_list->count-1;i>=0;i--) {
			if (!local_file_list->files[i]->basename) continue;
			if (remote_version < 19 &&
			    S_ISDIR(local_file_list->files[i]->mode))
				add_delete_entry(local_file_list->files[i]);
			if (-1 == flist_find(flist,local_file_list->files[i])) {
				delete_one(local_file_list->files[i]);
			}    
		}
		flist_free(local_file_list);
		free(name);
	}
}