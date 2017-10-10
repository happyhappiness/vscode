	printf("M %06"PRIo32" %s ", mode, dataref);
	quote_c_style(path, NULL, stdout, 0);
	putchar('\n');
}

void fast_export_begin_note(uint32_t revision, const char *author,
		const char *log, timestamp_t timestamp, const char *note_ref)
{
	static int firstnote = 1;
	size_t loglen = strlen(log);
	printf("commit %s\n", note_ref);
	printf("committer %s <%s@%s> %"PRItime" +0000\n", author, author, "local", timestamp);
	printf("data %"PRIuMAX"\n", (uintmax_t)loglen);
	fwrite(log, loglen, 1, stdout);
	if (firstnote) {
		if (revision > 1)
			printf("from %s^0", note_ref);
		firstnote = 0;
