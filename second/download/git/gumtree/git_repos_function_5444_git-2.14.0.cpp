static char *prune_directory(struct dir_struct *dir, struct pathspec *pathspec, int prefix)
{
	char *seen;
	int i;
	struct dir_entry **src, **dst;

	seen = xcalloc(pathspec->nr, 1);

	src = dst = dir->entries;
	i = dir->nr;
	while (--i >= 0) {
		struct dir_entry *entry = *src++;
		if (dir_path_match(entry, pathspec, prefix, seen))
			*dst++ = entry;
	}
	dir->nr = dst - dir->entries;
	add_pathspec_matches_against_index(pathspec, &the_index, seen);
	return seen;
}