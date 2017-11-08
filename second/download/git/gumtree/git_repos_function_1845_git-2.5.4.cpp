static struct untracked_cache_dir *lookup_untracked(struct untracked_cache *uc,
						    struct untracked_cache_dir *dir,
						    const char *name, int len)
{
	int first, last;
	struct untracked_cache_dir *d;
	if (!dir)
		return NULL;
	if (len && name[len - 1] == '/')
		len--;
	first = 0;
	last = dir->dirs_nr;
	while (last > first) {
		int cmp, next = (last + first) >> 1;
		d = dir->dirs[next];
		cmp = strncmp(name, d->name, len);
		if (!cmp && strlen(d->name) > len)
			cmp = -1;
		if (!cmp)
			return d;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}

	uc->dir_created++;
	d = xmalloc(sizeof(*d) + len + 1);
	memset(d, 0, sizeof(*d));
	memcpy(d->name, name, len);
	d->name[len] = '\0';

	ALLOC_GROW(dir->dirs, dir->dirs_nr + 1, dir->dirs_alloc);
	memmove(dir->dirs + first + 1, dir->dirs + first,
		(dir->dirs_nr - first) * sizeof(*dir->dirs));
	dir->dirs_nr++;
	dir->dirs[first] = d;
	return d;
}