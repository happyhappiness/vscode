static void copy_to_log(int fd)
{
	struct strbuf line = STRBUF_INIT;
	FILE *fp;

	fp = fdopen(fd, "r");
	if (fp == NULL) {
		logerror("fdopen of error channel failed");
		close(fd);
		return;
	}

	while (strbuf_getline_lf(&line, fp) != EOF) {
		logerror("%s", line.buf);
		strbuf_setlen(&line, 0);
	}

	strbuf_release(&line);
	fclose(fp);
}