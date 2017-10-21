
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

/*
 * Free up any resources a file_struct has allocated
 * and clear the file.
 */
void clear_file(struct file_struct *file, struct file_list *flist)
{
	if (flist->hlink_pool && file->link_u.idev)
		pool_free(flist->hlink_pool, 0, file->link_u.idev);
	memset(file, 0, file_struct_len);
	/* In an empty entry, dir.depth is an offset to the next non-empty
	 * entry.  Likewise for length in the opposite direction.  We assume
	 * that we're alone for now since flist_find() will adjust the counts
	 * it runs into that aren't up-to-date. */
	file->length = file->dir.depth = 1;
}

/*
 * allocate a new file list
 */
struct file_list *flist_new(int with_hlink, char *msg)
{
	struct file_list *flist;
