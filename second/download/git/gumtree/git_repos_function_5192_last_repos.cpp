static int switch_unborn_to_new_branch(const struct checkout_opts *opts)
{
	int status;
	struct strbuf branch_ref = STRBUF_INIT;

	if (!opts->new_branch)
		die(_("You are on a branch yet to be born"));
	strbuf_addf(&branch_ref, "refs/heads/%s", opts->new_branch);
	status = create_symref("HEAD", branch_ref.buf, "checkout -b");
	strbuf_release(&branch_ref);
	if (!opts->quiet)
		fprintf(stderr, _("Switched to a new branch '%s'\n"),
			opts->new_branch);
	return status;
}