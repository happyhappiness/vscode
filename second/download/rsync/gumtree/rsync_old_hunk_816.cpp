
	stats.flist_size = stats.total_read - start_read;
	stats.num_files = flist->count;

	return flist;

oom:
	out_of_memory("recv_file_list");
	return NULL;		/* not reached */
}


static int file_compare(struct file_struct **file1, struct file_struct **file2)
{
	return f_name_cmp(*file1, *file2);
}


/* Search for an identically-named item in the file list.  Note that the
 * items must agree in their directory-ness, or no match is returned. */
int flist_find(struct file_list *flist, struct file_struct *f)
{
	int low = flist->low, high = flist->high;
	int ret, mid, mid_up;

	while (low <= high) {
		mid = (low + high) / 2;
		for (mid_up = mid; !flist->files[mid_up]->basename; mid_up++) {}
		if (mid_up <= high)
			ret = f_name_cmp(flist->files[mid_up], f);
		else
			ret = 1;
		if (ret == 0) {
			if (protocol_version < 29
			    && S_ISDIR(flist->files[mid_up]->mode)
			    != S_ISDIR(f->mode))
				return -1;
			return mid_up;
		}
		if (ret > 0)
			high = mid - 1;
		else
			low = mid_up + 1;
	}
	return -1;
}


/*
 * Free up any resources a file_struct has allocated
 * and clear the file.
 */
void clear_file(int i, struct file_list *flist)
{
	if (flist->hlink_pool && flist->files[i]->link_u.idev)
		pool_free(flist->hlink_pool, 0, flist->files[i]->link_u.idev);
	memset(flist->files[i], 0, file_struct_len);
}


/*
 * allocate a new file list
 */
struct file_list *flist_new(int with_hlink, char *msg)
{
	struct file_list *flist;
