void send_file_name(int f, struct file_list *flist, char *fname,
		    int recursive, unsigned base_flags)
{
	struct file_struct *file;
	extern int delete_excluded;

	/* f is set to -1 when calculating deletion file list */
	file = make_file(fname, &flist->string_area,
			 f == -1 && delete_excluded? SERVER_EXCLUDES
						   : ALL_EXCLUDES);

	if (!file)
		return;

	maybe_emit_filelist_progress(flist);

	flist_expand(flist);

	if (write_batch)	/*  dw  */
		file->flags = FLAG_DELETE;

	if (file->basename[0]) {
		flist->files[flist->count++] = file;
		send_file_entry(file, f, base_flags);
	}

	if (S_ISDIR(file->mode) && recursive) {
		struct exclude_struct **last_exclude_list =
		    local_exclude_list;
		send_directory(f, flist, f_name(file));
		local_exclude_list = last_exclude_list;
		return;
	}
}