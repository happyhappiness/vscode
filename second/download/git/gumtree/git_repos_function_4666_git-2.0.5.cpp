static void shortlog(const char *name,
		     struct origin_data *origin_data,
		     struct commit *head,
		     struct rev_info *rev,
		     struct fmt_merge_msg_opts *opts,
		     struct strbuf *out)
{
	int i, count = 0;
	struct commit *commit;
	struct object *branch;
	struct string_list subjects = STRING_LIST_INIT_DUP;
	struct string_list authors = STRING_LIST_INIT_DUP;
	struct string_list committers = STRING_LIST_INIT_DUP;
	int flags = UNINTERESTING | TREESAME | SEEN | SHOWN | ADDED;
	struct strbuf sb = STRBUF_INIT;
	const unsigned char *sha1 = origin_data->sha1;
	int limit = opts->shortlog_len;

	branch = deref_tag(parse_object(sha1), sha1_to_hex(sha1), 40);
	if (!branch || branch->type != OBJ_COMMIT)
		return;

	setup_revisions(0, NULL, rev, NULL);
	add_pending_object(rev, branch, name);
	add_pending_object(rev, &head->object, "^HEAD");
	head->object.flags |= UNINTERESTING;
	if (prepare_revision_walk(rev))
		die("revision walk setup failed");
	while ((commit = get_revision(rev)) != NULL) {
		struct pretty_print_context ctx = {0};

		if (commit->parents && commit->parents->next) {
			/* do not list a merge but count committer */
			if (opts->credit_people)
				record_person('c', &committers, commit);
			continue;
		}
		if (!count && opts->credit_people)
			/* the 'tip' committer */
			record_person('c', &committers, commit);
		if (opts->credit_people)
			record_person('a', &authors, commit);
		count++;
		if (subjects.nr > limit)
			continue;

		format_commit_message(commit, "%s", &sb, &ctx);
		strbuf_ltrim(&sb);

		if (!sb.len)
			string_list_append(&subjects,
					   sha1_to_hex(commit->object.sha1));
		else
			string_list_append(&subjects, strbuf_detach(&sb, NULL));
	}

	if (opts->credit_people)
		add_people_info(out, &authors, &committers);
	if (count > limit)
		strbuf_addf(out, "\n* %s: (%d commits)\n", name, count);
	else
		strbuf_addf(out, "\n* %s:\n", name);

	if (origin_data->is_local_branch && use_branch_desc)
		add_branch_desc(out, name);

	for (i = 0; i < subjects.nr; i++)
		if (i >= limit)
			strbuf_addf(out, "  ...\n");
		else
			strbuf_addf(out, "  %s\n", subjects.items[i].string);

	clear_commit_marks((struct commit *)branch, flags);
	clear_commit_marks(head, flags);
	free_commit_list(rev->commits);
	rev->commits = NULL;
	rev->pending.nr = 0;

	string_list_clear(&authors, 0);
	string_list_clear(&committers, 0);
	string_list_clear(&subjects, 0);
}