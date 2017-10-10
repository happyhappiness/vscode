 *
 * Returns 1 if the patch should be skipped, 0 otherwise.
 */
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

