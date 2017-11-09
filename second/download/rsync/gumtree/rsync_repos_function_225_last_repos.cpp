void set_current_file_index(struct file_struct *file, int ndx)
{
	if (!file)
		current_file_index = cur_flist->used + cur_flist->ndx_start - 1;
	else if (need_unsorted_flist)
		current_file_index = flist_find(cur_flist, file) + cur_flist->ndx_start;
	else
		current_file_index = ndx;
	current_file_index -= cur_flist->flist_num;
}