static const char *path_path(void *obj)
{
	struct combine_diff_path *path = (struct combine_diff_path *)obj;

	return path->path;
}