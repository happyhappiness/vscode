static char *read_line_from_git_path(const char *filename)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *fp = fopen_or_warn(git_path("%s", filename), "r");

	if (!fp) {
		strbuf_release(&buf);
		return NULL;
	}
	strbuf_getline_lf(&buf, fp);
	if (!fclose(fp)) {
		return strbuf_detach(&buf, NULL);
	} else {
		strbuf_release(&buf);
		return NULL;
	}
}