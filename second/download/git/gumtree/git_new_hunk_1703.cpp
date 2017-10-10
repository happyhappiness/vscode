
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
