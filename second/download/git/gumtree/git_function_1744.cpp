tatic const char *find_author_by_nickname(const char *name)
{
	struct rev_info revs;
	struct commit *commit;
	struct strbuf buf = STRBUF_INIT;
	struct string_list mailmap = STRING_LIST_INIT_NODUP;
	const char *av[20];
	int ac = 0;

	init_revisions(&revs, NULL);
	strbuf_addf(&buf, "--author=%s", name);
	av[++ac] = "--all";
	av[++ac] = "-i";
	av[++ac] = buf.buf;
	av[++ac] = NULL;
	setup_revisions(ac, av, &revs, NULL);
	revs.mailmap = &mailmap;
	read_mailmap(revs.mailmap, NULL);

	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));
	commit = get_revision(&revs);
	if (commit) {
		struct pretty_print_context ctx = {0};
		ctx.date_mode = DATE_NORMAL;
		strbuf_release(&buf);
		format_commit_message(commit, "%aN <%aE>", &buf, &ctx);
		clear_mailmap(&mailmap);
		return strbuf_detach(&buf, NULL);
	}
	die(_("No existing author found with '%s'"), name);
}