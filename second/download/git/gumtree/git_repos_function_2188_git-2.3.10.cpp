static int get_message(struct commit *commit, struct commit_message *out)
{
	const char *abbrev, *subject;
	int abbrev_len, subject_len;
	char *q;

	if (!git_commit_encoding)
		git_commit_encoding = "UTF-8";

	out->message = logmsg_reencode(commit, NULL, git_commit_encoding);
	abbrev = find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV);
	abbrev_len = strlen(abbrev);

	subject_len = find_commit_subject(out->message, &subject);

	out->parent_label = xmalloc(strlen("parent of ") + abbrev_len +
			      strlen("... ") + subject_len + 1);
	q = out->parent_label;
	q = mempcpy(q, "parent of ", strlen("parent of "));
	out->label = q;
	q = mempcpy(q, abbrev, abbrev_len);
	q = mempcpy(q, "... ", strlen("... "));
	out->subject = q;
	q = mempcpy(q, subject, subject_len);
	*q = '\0';
	return 0;
}