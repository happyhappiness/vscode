static struct file_struct *send_file_name(int f, struct file_list *flist,
					  char *fname, STRUCT_STAT *stp,
					  unsigned short flags)
{
	struct file_struct *file;

	file = make_file(fname, flist, stp, flags,
			 f == -2 ? SERVER_FILTERS : ALL_FILTERS);
	if (!file)
		return NULL;

	if (chmod_modes && !S_ISLNK(file->mode))
		file->mode = tweak_mode(file->mode, chmod_modes);

	maybe_emit_filelist_progress(flist->count + flist_count_offset);

	flist_expand(flist);

	if (file->basename[0]) {
		flist->files[flist->count++] = file;
		send_file_entry(file, f);
	}
	return file;
}