	if (((old_mode ^ new_mode) & ~S_IFMT) &&
			chmod(path, (new_mode & ~S_IFMT)) < 0)
		return -2;
	return 0;
}

static int have_same_root(const char *path1, const char *path2)
{
	int is_abs1, is_abs2;

	is_abs1 = is_absolute_path(path1);
	is_abs2 = is_absolute_path(path2);
