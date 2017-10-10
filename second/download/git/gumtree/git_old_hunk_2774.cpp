	printf("committer-tz %s\n", ci.committer_tz.buf);
	printf("summary %s\n", ci.summary.buf);
	if (suspect->commit->object.flags & UNINTERESTING)
		printf("boundary\n");
	if (suspect->previous) {
		struct origin *prev = suspect->previous;
		printf("previous %s ", sha1_to_hex(prev->commit->object.sha1));
		write_name_quoted(prev->path, stdout, '\n');
	}

	commit_info_destroy(&ci);

	return 1;
