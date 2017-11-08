static int run_fallback_merge_recursive(const struct am_state *state,
					unsigned char *orig_tree,
					unsigned char *our_tree,
					unsigned char *his_tree)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int status;

	cp.git_cmd = 1;

	argv_array_pushf(&cp.env_array, "GITHEAD_%s=%.*s",
			 sha1_to_hex(his_tree), linelen(state->msg), state->msg);
	if (state->quiet)
		argv_array_push(&cp.env_array, "GIT_MERGE_VERBOSITY=0");

	argv_array_push(&cp.args, "merge-recursive");
	argv_array_push(&cp.args, sha1_to_hex(orig_tree));
	argv_array_push(&cp.args, "--");
	argv_array_push(&cp.args, sha1_to_hex(our_tree));
	argv_array_push(&cp.args, sha1_to_hex(his_tree));

	status = run_command(&cp) ? (-1) : 0;
	discard_cache();
	read_cache();
	return status;
}