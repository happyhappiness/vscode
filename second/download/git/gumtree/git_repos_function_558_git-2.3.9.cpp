static struct archiver *find_tar_filter(const char *name, int len)
{
	int i;
	for (i = 0; i < nr_tar_filters; i++) {
		struct archiver *ar = tar_filters[i];
		if (!strncmp(ar->name, name, len) && !ar->name[len])
			return ar;
	}
	return NULL;
}