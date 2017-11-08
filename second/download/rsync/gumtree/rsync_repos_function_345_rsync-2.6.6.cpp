static struct file_struct *send_file_name(int f, struct file_list *flist,
					  char *fname, unsigned short base_flags)
{
	struct file_struct *file;

	file = make_file(fname, flist, f == -2 ? SERVER_FILTERS : ALL_FILTERS);
	if (!file)
		return NULL;

	maybe_emit_filelist_progress(flist->count + flist_count_offset);

	flist_expand(flist);

	if (file->basename[0]) {
		flist->files[flist->count++] = file;
		send_file_entry(file, f, base_flags);
	}
	return file;
}