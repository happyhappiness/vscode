static int is_expected_rev(const struct object_id *oid)
{
	const char *filename = git_path_bisect_expected_rev();
	struct stat st;
	struct strbuf str = STRBUF_INIT;
	FILE *fp;
	int res = 0;

	if (stat(filename, &st) || !S_ISREG(st.st_mode))
		return 0;

	fp = fopen(filename, "r");
	if (!fp)
		return 0;

	if (strbuf_getline(&str, fp, '\n') != EOF)
		res = !strcmp(str.buf, oid_to_hex(oid));

	strbuf_release(&str);
	fclose(fp);

	return res;
}