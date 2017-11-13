static int emit_one_suspect_detail(struct origin *suspect, int repeat)
{
	struct commit_info ci;

	if (!repeat && (suspect->commit->object.flags & METAINFO_SHOWN))
		return 0;

	suspect->commit->object.flags |= METAINFO_SHOWN;
	get_commit_info(suspect->commit, &ci, 1);
	printf("author %s\n", ci.author.buf);
	printf("author-mail %s\n", ci.author_mail.buf);
	printf("author-time %lu\n", ci.author_time);
	printf("author-tz %s\n", ci.author_tz.buf);
	printf("committer %s\n", ci.committer.buf);
	printf("committer-mail %s\n", ci.committer_mail.buf);
	printf("committer-time %lu\n", ci.committer_time);
	printf("committer-tz %s\n", ci.committer_tz.buf);
	printf("summary %s\n", ci.summary.buf);
	if (suspect->commit->object.flags & UNINTERESTING)
		printf("boundary\n");

	commit_info_destroy(&ci);

	return 1;
}