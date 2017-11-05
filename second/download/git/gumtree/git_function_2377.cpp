static int update_info_file(char *path, int (*generate)(FILE *))
{
	char *tmp = mkpathdup("%s_XXXXXX", path);
	int ret = -1;
	int fd = -1;
	FILE *fp = NULL;

	safe_create_leading_directories(path);
	fd = git_mkstemp_mode(tmp, 0666);
	if (fd < 0)
		goto out;
	fp = fdopen(fd, "w");
	if (!fp)
		goto out;
	ret = generate(fp);
	if (ret)
		goto out;
	if (fclose(fp))
		goto out;
	if (adjust_shared_perm(tmp) < 0)
		goto out;
	if (rename(tmp, path) < 0)
		goto out;
	ret = 0;

out:
	if (ret) {
		error("unable to update %s: %s", path, strerror(errno));
		if (fp)
			fclose(fp);
		else if (fd >= 0)
			close(fd);
		unlink(tmp);
	}
	free(tmp);
	return ret;
}