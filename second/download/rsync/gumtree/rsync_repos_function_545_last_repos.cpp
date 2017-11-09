int flist_find(struct file_list *flist, struct file_struct *f)
{
	int low = flist->low, high = flist->high;
	int diff, mid, mid_up;

	while (low <= high) {
		mid = (low + high) / 2;
		if (F_IS_ACTIVE(flist->sorted[mid]))
			mid_up = mid;
		else {
			/* Scan for the next non-empty entry using the cached
			 * distance values.  If the value isn't fully up-to-
			 * date, update it. */
			mid_up = mid + F_DEPTH(flist->sorted[mid]);
			if (!F_IS_ACTIVE(flist->sorted[mid_up])) {
				do {
				    mid_up += F_DEPTH(flist->sorted[mid_up]);
				} while (!F_IS_ACTIVE(flist->sorted[mid_up]));
				F_DEPTH(flist->sorted[mid]) = mid_up - mid;
			}
			if (mid_up > high) {
				/* If there's nothing left above us, set high to
				 * a non-empty entry below us and continue. */
				high = mid - (int)flist->sorted[mid]->len32;
				if (!F_IS_ACTIVE(flist->sorted[high])) {
					do {
					    high -= (int)flist->sorted[high]->len32;
					} while (!F_IS_ACTIVE(flist->sorted[high]));
					flist->sorted[mid]->len32 = mid - high;
				}
				continue;
			}
		}
		diff = f_name_cmp(flist->sorted[mid_up], f);
		if (diff == 0) {
			if (protocol_version < 29
			    && S_ISDIR(flist->sorted[mid_up]->mode)
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