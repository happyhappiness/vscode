static int read_ancestry(const char *graft_file)
{
	FILE *fp = fopen_or_warn(graft_file, "r");
	struct strbuf buf = STRBUF_INIT;
	if (!fp)
		return -1;
	while (!strbuf_getwholeline(&buf, fp, '\n')) {
		/* The format is just "Commit Parent1 Parent2 ...\n" */
		struct commit_graft *graft = read_graft_line(buf.buf, buf.len);
		if (graft)
			register_commit_graft(graft, 0);
	}
	fclose(fp);
	strbuf_release(&buf);
	return 0;
}