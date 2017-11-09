static int setup_tmp_objdir(const char *root)
{
	char *path;
	int ret = 0;

	path = xstrfmt("%s/pack", root);
	ret = mkdir(path, 0777);
	free(path);

	return ret;
}