static int do_interactive(struct am_state *state)
{
	assert(state->msg);

	if (!isatty(0))
		die(_("cannot be interactive without stdin connected to a terminal."));

	for (;;) {
		const char *reply;

		puts(_("Commit Body is:"));
		puts("--------------------------");
		printf("%s", state->msg);
		puts("--------------------------");

		/*
		 * TRANSLATORS: Make sure to include [y], [n], [e], [v] and [a]
		 * in your translation. The program will only accept English
		 * input at this point.
		 */
		reply = git_prompt(_("Apply? [y]es/[n]o/[e]dit/[v]iew patch/[a]ccept all: "), PROMPT_ECHO);

		if (!reply) {
			continue;
		} else if (*reply == 'y' || *reply == 'Y') {
			return 0;
		} else if (*reply == 'a' || *reply == 'A') {
			state->interactive = 0;
			return 0;
		} else if (*reply == 'n' || *reply == 'N') {
			return 1;
		} else if (*reply == 'e' || *reply == 'E') {
			struct strbuf msg = STRBUF_INIT;

			if (!launch_editor(am_path(state, "final-commit"), &msg, NULL)) {
				free(state->msg);
				state->msg = strbuf_detach(&msg, &state->msg_len);
			}
			strbuf_release(&msg);
		} else if (*reply == 'v' || *reply == 'V') {
			const char *pager = git_pager(1);
			struct child_process cp = CHILD_PROCESS_INIT;

			if (!pager)
				pager = "cat";
			prepare_pager_args(&cp, pager);
			argv_array_push(&cp.args, am_path(state, "patch"));
			run_command(&cp);
		}
	}
}