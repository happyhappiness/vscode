	printf("committer-mail %s\n", ci.committer_mail.buf);
	printf("committer-time %lu\n", ci.committer_time);
	printf("committer-tz %s\n", ci.committer_tz.buf);
	printf("summary %s\n", ci.summary.buf);
	if (suspect->commit->object.flags & UNINTERESTING)
		printf("boundary\n");

	commit_info_destroy(&ci);

	return 1;
}

