
	check_aliased_updates(commands);

	free(head_name_to_free);
	head_name = head_name_to_free = resolve_refdup("HEAD", 0, sha1, NULL);

	if (use_atomic)
		execute_commands_atomic(commands, si);
	else
		execute_commands_non_atomic(commands, si);

	if (shallow_update)
		warn_if_skipped_connectivity_check(commands, si);
}

static struct command **queue_command(struct command **tail,
				      const char *line,
				      int linelen)
{
