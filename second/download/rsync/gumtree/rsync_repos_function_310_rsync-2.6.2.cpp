void send_file_name(int f, struct file_list *flist, char *fname,
		    int recursive, unsigned short base_flags)
{
	struct file_struct *file;
	char fbuf[MAXPATHLEN];
	extern int delete_excluded;

	/* f is set to -1 when calculating deletion file list */
	file = make_file(fname, flist,
	    f == -1 && delete_excluded? SERVER_EXCLUDES : ALL_EXCLUDES);

	if (!file)
		return;

	maybe_emit_filelist_progress(flist);

	flist_expand(flist);

	if (write_batch)
		file->flags |= FLAG_TOP_DIR;

	if (file->basename[0]) {
		flist->files[flist->count++] = file;
		send_file_entry(file, f, base_flags);
	}

	if (recursive && S_ISDIR(file->mode)
	    && !(file->flags & FLAG_MOUNT_POINT)) {
		struct exclude_list_struct last_list = local_exclude_list;
		local_exclude_list.head = local_exclude_list.tail = NULL;
		send_directory(f, flist, f_name_to(file, fbuf));
		free_exclude_list(&local_exclude_list);
		local_exclude_list = last_list;
	}
}