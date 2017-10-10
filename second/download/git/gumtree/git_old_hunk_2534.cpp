static int suggest_conflicts(void)
{
	const char *filename;
	FILE *fp;
	struct strbuf msgbuf = STRBUF_INIT;

	filename = git_path("MERGE_MSG");
	fp = fopen(filename, "a");
	if (!fp)
		die_errno(_("Could not open '%s' for writing"), filename);

	append_conflicts_hint(&msgbuf);
	fputs(msgbuf.buf, fp);
