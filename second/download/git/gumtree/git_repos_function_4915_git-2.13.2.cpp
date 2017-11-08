static int too_many_loose_objects(void)
{
	/*
	 * Quickly check if a "gc" is needed, by estimating how
	 * many loose objects there are.  Because SHA-1 is evenly
	 * distributed, we can check only one and get a reasonable
	 * estimate.
	 */
	DIR *dir;
	struct dirent *ent;
	int auto_threshold;
	int num_loose = 0;
	int needed = 0;

	if (gc_auto_threshold <= 0)
		return 0;

	dir = opendir(git_path("objects/17"));
	if (!dir)
		return 0;

	auto_threshold = (gc_auto_threshold + 255) / 256;
	while ((ent = readdir(dir)) != NULL) {
		if (strspn(ent->d_name, "0123456789abcdef") != 38 ||
		    ent->d_name[38] != '\0')
			continue;
		if (++num_loose > auto_threshold) {
			needed = 1;
			break;
		}
	}
	closedir(dir);
	return needed;
}