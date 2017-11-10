static int is_expected_rev(const unsigned char *sha1)
{
	const char *filename = git_path("BISECT_EXPECTED_REV");
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
		res = !strcmp(str.buf, sha1_to_hex(sha1));

	strbuf_release(&str);
	fclose(fp);

	return res;
}