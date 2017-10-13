static void handle_commit(struct commit *commit, struct rev_info *rev)
{
	int saved_output_format = rev->diffopt.output_format;
	const char *commit_buffer;
	const char *author, *author_end, *committer, *committer_end;
	const char *encoding, *message;
	char *reencoded = NULL;
	struct commit_list *p;
	const char *refname;
	int i;

	rev->diffopt.output_format = DIFF_FORMAT_CALLBACK;

	parse_commit_or_die(commit);
	commit_buffer = get_commit_buffer(commit, NULL);
	author = strstr(commit_buffer, "\nauthor ");
	if (!author)
		die ("Could not find author in commit %s",
		     sha1_to_hex(commit->object.sha1));
	author++;
	author_end = strchrnul(author, '\n');
	committer = strstr(author_end, "\ncommitter ");
	if (!committer)
		die ("Could not find committer in commit %s",
		     sha1_to_hex(commit->object.sha1));
	committer++;
	committer_end = strchrnul(committer, '\n');
	message = strstr(committer_end, "\n\n");
	encoding = find_encoding(committer_end, message);
	if (message)
		message += 2;

	if (commit->parents &&
	    get_object_mark(&commit->parents->item->object) != 0 &&
	    !full_tree) {
		parse_commit_or_die(commit->parents->item);
		diff_tree_sha1(commit->parents->item->tree->object.sha1,
			       commit->tree->object.sha1, "", &rev->diffopt);
	}
	else
		diff_root_tree_sha1(commit->tree->object.sha1,
				    "", &rev->diffopt);

	/* Export the referenced blobs, and remember the marks. */
	for (i = 0; i < diff_queued_diff.nr; i++)
		if (!S_ISGITLINK(diff_queued_diff.queue[i]->two->mode))
			export_blob(diff_queued_diff.queue[i]->two->sha1);

	refname = commit->util;
	if (anonymize) {
		refname = anonymize_refname(refname);
		anonymize_ident_line(&committer, &committer_end);
		anonymize_ident_line(&author, &author_end);
	}

	mark_next_object(&commit->object);
	if (anonymize)
		reencoded = anonymize_commit_message(message);
	else if (!is_encoding_utf8(encoding))
		reencoded = reencode_string(message, "UTF-8", encoding);
	if (!commit->parents)
		printf("reset %s\n", refname);
	printf("commit %s\nmark :%"PRIu32"\n%.*s\n%.*s\ndata %u\n%s",
	       refname, last_idnum,
	       (int)(author_end - author), author,
	       (int)(committer_end - committer), committer,
	       (unsigned)(reencoded
			  ? strlen(reencoded) : message
			  ? strlen(message) : 0),
	       reencoded ? reencoded : message ? message : "");
	free(reencoded);
	unuse_commit_buffer(commit, commit_buffer);

	for (i = 0, p = commit->parents; p; p = p->next) {
		int mark = get_object_mark(&p->item->object);
		if (!mark)
			continue;
		if (i == 0)
			printf("from :%d\n", mark);
		else
			printf("merge :%d\n", mark);
		i++;
	}

	if (full_tree)
		printf("deleteall\n");
	log_tree_diff_flush(rev);
	rev->diffopt.output_format = saved_output_format;

	printf("\n");

	show_progress();
}