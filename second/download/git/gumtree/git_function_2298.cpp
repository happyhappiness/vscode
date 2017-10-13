static int parse_mail(struct am_state *state, const char *mail)
{
	FILE *fp;
	struct strbuf sb = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
	struct strbuf author_name = STRBUF_INIT;
	struct strbuf author_date = STRBUF_INIT;
	struct strbuf author_email = STRBUF_INIT;
	int ret = 0;
	struct mailinfo mi;

	setup_mailinfo(&mi);

	if (state->utf8)
		mi.metainfo_charset = get_commit_output_encoding();
	else
		mi.metainfo_charset = NULL;

	switch (state->keep) {
	case KEEP_FALSE:
		break;
	case KEEP_TRUE:
		mi.keep_subject = 1;
		break;
	case KEEP_NON_PATCH:
		mi.keep_non_patch_brackets_in_subject = 1;
		break;
	default:
		die("BUG: invalid value for state->keep");
	}

	if (state->message_id)
		mi.add_message_id = 1;

	switch (state->scissors) {
	case SCISSORS_UNSET:
		break;
	case SCISSORS_FALSE:
		mi.use_scissors = 0;
		break;
	case SCISSORS_TRUE:
		mi.use_scissors = 1;
		break;
	default:
		die("BUG: invalid value for state->scissors");
	}

	mi.input = fopen(mail, "r");
	if (!mi.input)
		die("could not open input");
	mi.output = fopen(am_path(state, "info"), "w");
	if (!mi.output)
		die("could not open output 'info'");
	if (mailinfo(&mi, am_path(state, "msg"), am_path(state, "patch")))
		die("could not parse patch");

	fclose(mi.input);
	fclose(mi.output);

	/* Extract message and author information */
	fp = xfopen(am_path(state, "info"), "r");
	while (!strbuf_getline(&sb, fp, '\n')) {
		const char *x;

		if (skip_prefix(sb.buf, "Subject: ", &x)) {
			if (msg.len)
				strbuf_addch(&msg, '\n');
			strbuf_addstr(&msg, x);
		} else if (skip_prefix(sb.buf, "Author: ", &x))
			strbuf_addstr(&author_name, x);
		else if (skip_prefix(sb.buf, "Email: ", &x))
			strbuf_addstr(&author_email, x);
		else if (skip_prefix(sb.buf, "Date: ", &x))
			strbuf_addstr(&author_date, x);
	}
	fclose(fp);

	/* Skip pine's internal folder data */
	if (!strcmp(author_name.buf, "Mail System Internal Data")) {
		ret = 1;
		goto finish;
	}

	if (is_empty_file(am_path(state, "patch"))) {
		printf_ln(_("Patch is empty. Was it split wrong?"));
		die_user_resolve(state);
	}

	strbuf_addstr(&msg, "\n\n");
	strbuf_addbuf(&msg, &mi.log_message);
	strbuf_stripspace(&msg, 0);

	if (state->signoff)
		am_signoff(&msg);

	assert(!state->author_name);
	state->author_name = strbuf_detach(&author_name, NULL);

	assert(!state->author_email);
	state->author_email = strbuf_detach(&author_email, NULL);

	assert(!state->author_date);
	state->author_date = strbuf_detach(&author_date, NULL);

	assert(!state->msg);
	state->msg = strbuf_detach(&msg, &state->msg_len);

finish:
	strbuf_release(&msg);
	strbuf_release(&author_date);
	strbuf_release(&author_email);
	strbuf_release(&author_name);
	strbuf_release(&sb);
	clear_mailinfo(&mi);
	return ret;
}