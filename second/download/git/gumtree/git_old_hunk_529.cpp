	if (!empty_commit)
		return 0;
	else
		return 1;
}

static int do_pick_commit(struct commit *commit, struct replay_opts *opts)
{
	unsigned char head[20];
	struct commit *base, *next, *parent;
	const char *base_label, *next_label;
	struct commit_message msg = { NULL, NULL, NULL, NULL };
	struct strbuf msgbuf = STRBUF_INIT;
