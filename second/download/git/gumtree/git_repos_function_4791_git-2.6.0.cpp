static void am_setup(struct am_state *state, enum patch_format patch_format,
			const char **paths, int keep_cr)
{
	unsigned char curr_head[GIT_SHA1_RAWSZ];
	const char *str;
	struct strbuf sb = STRBUF_INIT;

	if (!patch_format)
		patch_format = detect_patch_format(paths);

	if (!patch_format) {
		fprintf_ln(stderr, _("Patch format detection failed."));
		exit(128);
	}

	if (mkdir(state->dir, 0777) < 0 && errno != EEXIST)
		die_errno(_("failed to create directory '%s'"), state->dir);

	if (split_mail(state, patch_format, paths, keep_cr) < 0) {
		am_destroy(state);
		die(_("Failed to split patches."));
	}

	if (state->rebasing)
		state->threeway = 1;

	write_state_bool(state, "threeway", state->threeway);
	write_state_bool(state, "quiet", state->quiet);
	write_state_bool(state, "sign", state->signoff);
	write_state_bool(state, "utf8", state->utf8);

	switch (state->keep) {
	case KEEP_FALSE:
		str = "f";
		break;
	case KEEP_TRUE:
		str = "t";
		break;
	case KEEP_NON_PATCH:
		str = "b";
		break;
	default:
		die("BUG: invalid value for state->keep");
	}

	write_state_text(state, "keep", str);
	write_state_bool(state, "messageid", state->message_id);

	switch (state->scissors) {
	case SCISSORS_UNSET:
		str = "";
		break;
	case SCISSORS_FALSE:
		str = "f";
		break;
	case SCISSORS_TRUE:
		str = "t";
		break;
	default:
		die("BUG: invalid value for state->scissors");
	}
	write_state_text(state, "scissors", str);

	sq_quote_argv(&sb, state->git_apply_opts.argv, 0);
	write_state_text(state, "apply-opt", sb.buf);

	if (state->rebasing)
		write_state_text(state, "rebasing", "");
	else
		write_state_text(state, "applying", "");

	if (!get_sha1("HEAD", curr_head)) {
		write_state_text(state, "abort-safety", sha1_to_hex(curr_head));
		if (!state->rebasing)
			update_ref("am", "ORIG_HEAD", curr_head, NULL, 0,
					UPDATE_REFS_DIE_ON_ERR);
	} else {
		write_state_text(state, "abort-safety", "");
		if (!state->rebasing)
			delete_ref("ORIG_HEAD", NULL, 0);
	}

	/*
	 * NOTE: Since the "next" and "last" files determine if an am_state
	 * session is in progress, they should be written last.
	 */

	write_state_count(state, "next", state->cur);
	write_state_count(state, "last", state->last);

	strbuf_release(&sb);
}