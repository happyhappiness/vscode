static int update_info_file(char *path, int (*generate)(FILE *))
{
	char *tmp = mkpathdup("%s_XXXXXX", path);
	int ret = -1;
	int fd = -1;
	FILE *fp = NULL, *to_close;

	safe_create_leading_directories(path);
	fd = git_mkstemp_mode(tmp, 0666);
	if (fd < 0)
		goto out;
	to_close = fp = fdopen(fd, "w");
	if (!fp)
		goto out;
	fd = -1;
	ret = generate(fp);
	if (ret)
		goto out;
	fp = NULL;
	if (fclose(to_close))
		goto out;
	if (adjust_shared_perm(tmp) < 0)
		goto out;
	if (rename(tmp, path) < 0)
		goto out;
	ret = 0;

out:
	if (ret) {
		error_errno("unable to update %s", path);
		if (fp)
			fclose(fp);
		else if (fd >= 0)
			close(fd);
		unlink(tmp);
	}
	free(tmp);
	return ret;
}