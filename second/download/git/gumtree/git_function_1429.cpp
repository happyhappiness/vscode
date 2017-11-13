void fast_export_begin_commit(uint32_t revision, const char *author,
			const struct strbuf *log,
			const char *uuid, const char *url,
			unsigned long timestamp, const char *local_ref)
{
	static const struct strbuf empty = STRBUF_INIT;
	if (!log)
		log = &empty;
	if (*uuid && *url) {
		snprintf(gitsvnline, MAX_GITSVN_LINE_LEN,
				"\n\ngit-svn-id: %s@%"PRIu32" %s\n",
				 url, revision, uuid);
	} else {
		*gitsvnline = '\0';
	}
	printf("commit %s\n", local_ref);
	printf("mark :%"PRIu32"\n", revision);
	printf("committer %s <%s@%s> %lu +0000\n",
		   *author ? author : "nobody",
		   *author ? author : "nobody",
		   *uuid ? uuid : "local", timestamp);
	printf("data %"PRIuMAX"\n",
		(uintmax_t) (log->len + strlen(gitsvnline)));
	fwrite(log->buf, log->len, 1, stdout);
	printf("%s\n", gitsvnline);
	if (!first_commit_done) {
		if (revision > 1)
			printf("from :%"PRIu32"\n", revision - 1);
		first_commit_done = 1;
	}
}