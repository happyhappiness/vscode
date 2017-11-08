static void warn_if_skipped_connectivity_check(struct command *commands,
					       struct shallow_info *si)
{
	struct command *cmd;
	int checked_connectivity = 1;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (should_process_cmd(cmd) && si->shallow_ref[cmd->index]) {
			error("BUG: connectivity check has not been run on ref %s",
			      cmd->ref_name);
			checked_connectivity = 0;
		}
	}
	if (!checked_connectivity)
		die("BUG: connectivity check skipped???");
}