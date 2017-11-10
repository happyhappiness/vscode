static void get_from_rev(struct rev_info *rev, struct shortlog *log)
{
	struct commit *commit;

	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));
	while ((commit = get_revision(rev)) != NULL)
		shortlog_add_commit(log, commit);
}