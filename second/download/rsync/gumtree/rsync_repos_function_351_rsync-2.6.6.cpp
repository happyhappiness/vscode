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