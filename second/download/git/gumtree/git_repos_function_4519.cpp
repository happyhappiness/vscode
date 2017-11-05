static const char *read_commit_message(const char *name)
{
	const char *out_enc;
	struct commit *commit;

	commit = lookup_commit_reference_by_name(name);
	if (!commit)
		die(_("could not lookup commit %s"), name);
	out_enc = get_commit_output_encoding();
	return logmsg_reencode(commit, NULL, out_enc);
}