}

static int cmd_log_walk(struct rev_info *rev)
{
	struct commit *commit;
	int saved_nrl = 0;
	int saved_dcctc = 0;

	if (rev->early_output)
		setup_early_output(rev);

	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));
