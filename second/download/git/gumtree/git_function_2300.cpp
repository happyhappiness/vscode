static int parse_mail(struct am_state *state, const char *mail)
{
	FILE *fp;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf sb = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
	struct strbuf author_name = STRBUF_INIT;
	struct strbuf author_date = STRBUF_INIT;
	struct strbuf author_email = STRBUF_INIT;
	int ret = 0;

	cp.git_cmd = 1;
	cp.in = xopen(mail, O_RDONLY, 0);
	cp.out = xopen(am_path(state, "info"), O_WRONLY | O_CREAT, 0777);

	argv_array_push(&cp.args, "mailinfo");
	argv_array_push(&cp.args, state->utf8 ? "-u" : "-n");

	switch (state->keep) {
	case KEEP_FALSE:
		break;
	case KEEP_TRUE:
		argv_array_push(&cp.args, "-k");
		break;
	case KEEP_NON_PATCH:
		argv_array_push(&cp.args, "-b");
		break;
	default:
		die("BUG: invalid value for state->keep");
	}

	if (state->message_id)
		argv_array_push(&cp.args, "-m");

	switch (state->scissors) {
	case SCISSORS_UNSET:
		break;
	case SCISSORS_FALSE:
		argv_array_push(&cp.args, "--no-scissors");
		break;
	case SCISSORS_TRUE:
		argv_array_push(&cp.args, "--scissors");
		break;
	default:
		die("BUG: invalid value for state->scissors");
	}

	argv_array_push(&cp.args, am_path(state, "msg"));
	argv_array_push(&cp.args, am_path(state, "patch"));

	if (run_command(&cp) < 0)
		die("could not parse patch");

	close(cp.in);
	close(cp.out);

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
	if (strbuf_read_file(&msg, am_path(state, "msg"), 0) < 0)
		die_errno(_("could not read '%s'"), am_path(state, "msg"));
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
	return ret;
}