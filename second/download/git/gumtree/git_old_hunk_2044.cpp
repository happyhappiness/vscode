
	check_aliased_updates(commands);

	free(head_name_to_free);
	head_name = head_name_to_free = resolve_refdup("HEAD", 0, sha1, NULL);

	checked_connectivity = 1;
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string)
			continue;

		if (cmd->skip_update)
			continue;

		cmd->error_string = update(cmd, si);
		if (shallow_update && !cmd->error_string &&
		    si->shallow_ref[cmd->index]) {
			error("BUG: connectivity check has not been run on ref %s",
			      cmd->ref_name);
			checked_connectivity = 0;
		}
	}

	if (shallow_update && !checked_connectivity)
		error("BUG: run 'git fsck' for safety.\n"
		      "If there are errors, try to remove "
		      "the reported refs above");
}

static struct command **queue_command(struct command **tail,
				      const char *line,
				      int linelen)
{
