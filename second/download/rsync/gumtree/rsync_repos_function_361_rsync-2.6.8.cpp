int flist_find(struct file_list *flist, struct file_struct *f)
{
	int low = flist->low, high = flist->high;
	int diff, mid, mid_up;

	while (low <= high) {
		mid = (low + high) / 2;
		if (flist->files[mid]->basename)
			mid_up = mid;
		else {
			/* Scan for the next non-empty entry using the cached
			 * distance values.  If the value isn't fully up-to-
			 * date, update it. */
			mid_up = mid + flist->files[mid]->dir.depth;
			if (!flist->files[mid_up]->basename) {
				do {
				    mid_up += flist->files[mid_up]->dir.depth;
				} while (!flist->files[mid_up]->basename);
				flist->files[mid]->dir.depth = mid_up - mid;
			}
			if (mid_up > high) {
				/* If there's nothing left above us, set high to
				 * a non-empty entry below us and continue. */
				high = mid - flist->files[mid]->length;
				if (!flist->files[high]->basename) {
					do {
					    high -= flist->files[high]->length;
					} while (!flist->files[high]->basename);
					flist->files[mid]->length = mid - high;
				}
				continue;
			}
		}
		diff = f_name_cmp(flist->files[mid_up], f);
		if (diff == 0) {
			if (protocol_version < 29
			    && S_ISDIR(flist->files[mid_up]->mode)
			    != S_ISDIR(f->mode))
				return -1;
			return mid_up;
		}
		if (diff < 0)
			low = mid_up + 1;
		else
			high = mid - 1;
	}
	return -1;
}