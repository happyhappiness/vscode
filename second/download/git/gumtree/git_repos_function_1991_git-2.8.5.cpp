static int git_path_check_merge(const char *path, struct git_attr_check check[2])
{
	if (!check[0].attr) {
		check[0].attr = git_attr("merge");
		check[1].attr = git_attr("conflict-marker-size");
	}
	return git_check_attr(path, 2, check);
}