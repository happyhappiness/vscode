{
	const char *filename;
	FILE *fp;
	struct strbuf msgbuf = STRBUF_INIT;

	filename = git_path_merge_msg();
	fp = xfopen(filename, "a");

	append_conflicts_hint(&msgbuf);
	fputs(msgbuf.buf, fp);
	strbuf_release(&msgbuf);
	fclose(fp);
	rerere(allow_rerere_auto);
