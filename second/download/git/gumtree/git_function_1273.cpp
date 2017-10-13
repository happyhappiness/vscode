static int suggest_conflicts(void)
{
	const char *filename;
	FILE *fp;
	struct strbuf msgbuf = STRBUF_INIT;

	filename = git_path_merge_msg();
	fp = fopen(filename, "a");
	if (!fp)
		die_errno(_("Could not open '%s' for writing"), filename);

	append_conflicts_hint(&msgbuf);
	fputs(msgbuf.buf, fp);
	strbuf_release(&msgbuf);
	fclose(fp);
	rerere(allow_rerere_auto);
	printf(_("Automatic merge failed; "
			"fix conflicts and then commit the result.\n"));
	return 1;
}