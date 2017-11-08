static int format_todo(struct strbuf *buf, struct commit_list *todo_list,
		struct replay_opts *opts)
{
	struct commit_list *cur = NULL;
	const char *sha1_abbrev = NULL;
	const char *action_str = opts->action == REPLAY_REVERT ? "revert" : "pick";
	const char *subject;
	int subject_len;

	for (cur = todo_list; cur; cur = cur->next) {
		const char *commit_buffer = get_commit_buffer(cur->item, NULL);
		sha1_abbrev = find_unique_abbrev(cur->item->object.oid.hash, DEFAULT_ABBREV);
		subject_len = find_commit_subject(commit_buffer, &subject);
		strbuf_addf(buf, "%s %s %.*s\n", action_str, sha1_abbrev,
			subject_len, subject);
		unuse_commit_buffer(cur->item, commit_buffer);
	}
	return 0;
}