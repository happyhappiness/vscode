static void squash_message(struct commit *commit, struct commit_list *remoteheads)
{
	struct rev_info rev;
	struct strbuf out = STRBUF_INIT;
	struct commit_list *j;
	const char *filename;
	int fd;
	struct pretty_print_context ctx = {0};

	printf(_("Squash commit -- not updating HEAD\n"));
	filename = git_path_squash_msg();
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not write to '%s'"), filename);

	init_revisions(&rev, NULL);
	rev.ignore_merges = 1;
	rev.commit_format = CMIT_FMT_MEDIUM;

	commit->object.flags |= UNINTERESTING;
	add_pending_object(&rev, &commit->object, NULL);

	for (j = remoteheads; j; j = j->next)
		add_pending_object(&rev, &j->item->object, NULL);

	setup_revisions(0, NULL, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die(_("revision walk setup failed"));

	ctx.abbrev = rev.abbrev;
	ctx.date_mode = rev.date_mode;
	ctx.fmt = rev.commit_format;

	strbuf_addstr(&out, "Squashed commit of the following:\n");
	while ((commit = get_revision(&rev)) != NULL) {
		strbuf_addch(&out, '\n');
		strbuf_addf(&out, "commit %s\n",
			oid_to_hex(&commit->object.oid));
		pretty_print_commit(&ctx, commit, &out);
	}
	if (write_in_full(fd, out.buf, out.len) != out.len)
		die_errno(_("Writing SQUASH_MSG"));
	if (close(fd))
		die_errno(_("Finishing SQUASH_MSG"));
	strbuf_release(&out);
}