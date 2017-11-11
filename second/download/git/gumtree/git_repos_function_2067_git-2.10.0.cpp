static struct exclude *last_exclude_matching_from_lists(struct dir_struct *dir,
		const char *pathname, int pathlen, const char *basename,
		int *dtype_p)
{
	int i, j;
	struct exclude_list_group *group;
	struct exclude *exclude;
	for (i = EXC_CMDL; i <= EXC_FILE; i++) {
		group = &dir->exclude_list_group[i];
		for (j = group->nr - 1; j >= 0; j--) {
			exclude = last_exclude_matching_from_list(
				pathname, pathlen, basename, dtype_p,
				&group->el[j]);
			if (exclude)
				return exclude;
		}
	}
	return NULL;
}