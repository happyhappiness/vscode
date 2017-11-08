int flist_find(struct file_list *flist, struct file_struct *f)
{
	int low = 0, high = flist->count - 1;

	if (flist->count <= 0)
		return -1;

	while (low != high) {
		int mid = (low + high) / 2;
		int ret =
		    file_compare(&flist->files[flist_up(flist, mid)], &f);
		if (ret == 0)
			return flist_up(flist, mid);
		if (ret > 0) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}

	if (file_compare(&flist->files[flist_up(flist, low)], &f) == 0)
		return flist_up(flist, low);
	return -1;
}