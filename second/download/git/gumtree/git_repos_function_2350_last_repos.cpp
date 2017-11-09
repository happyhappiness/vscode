static struct attr_stack *read_attr_from_file(const char *path, int macro_ok)
{
	FILE *fp = fopen_or_warn(path, "r");
	struct attr_stack *res;
	char buf[2048];
	int lineno = 0;

	if (!fp)
		return NULL;
	res = xcalloc(1, sizeof(*res));
	while (fgets(buf, sizeof(buf), fp)) {
		char *bufp = buf;
		if (!lineno)
			skip_utf8_bom(&bufp, strlen(bufp));
		handle_attr_line(res, bufp, path, ++lineno, macro_ok);
	}
	fclose(fp);
	return res;
}