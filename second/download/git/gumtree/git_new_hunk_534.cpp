		return error(_("cannot resolve HEAD"));
	if (is_null_sha1(head_sha1))
		return error(_("cannot abort from a branch yet to be born"));
	return reset_for_rollback(head_sha1);
}

int sequencer_rollback(struct replay_opts *opts)
{
	FILE *f;
	unsigned char sha1[20];
	struct strbuf buf = STRBUF_INIT;

	f = fopen(git_path_head_file(), "r");
