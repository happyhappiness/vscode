int is_repository_shallow(void)
{
	FILE *fp;
	char buf[1024];
	const char *path = alternate_shallow_file;

	if (is_shallow >= 0)
		return is_shallow;

	if (!path)
		path = git_path_shallow();
	/*
	 * fetch-pack sets '--shallow-file ""' as an indicator that no
	 * shallow file should be used. We could just open it and it
	 * will likely fail. But let's do an explicit check instead.
	 */
	if (!*path || (fp = fopen(path, "r")) == NULL) {
		stat_validity_clear(&shallow_stat);
		is_shallow = 0;
		return is_shallow;
	}
	stat_validity_update(&shallow_stat, fileno(fp));
	is_shallow = 1;

	while (fgets(buf, sizeof(buf), fp)) {
		struct object_id oid;
		if (get_oid_hex(buf, &oid))
			die("bad shallow line: %s", buf);
		register_shallow(&oid);
	}
	fclose(fp);
	return is_shallow;
}