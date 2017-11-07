static struct cmd2process *start_multi_file_filter(struct hashmap *hashmap, const char *cmd)
{
	int err;
	struct cmd2process *entry;
	struct child_process *process;
	const char *argv[] = { cmd, NULL };
	struct string_list cap_list = STRING_LIST_INIT_NODUP;
	char *cap_buf;
	const char *cap_name;

	entry = xmalloc(sizeof(*entry));
	entry->cmd = cmd;
	entry->supported_capabilities = 0;
	process = &entry->process;

	child_process_init(process);
	process->argv = argv;
	process->use_shell = 1;
	process->in = -1;
	process->out = -1;
	process->clean_on_exit = 1;
	process->clean_on_exit_handler = stop_multi_file_filter;

	if (start_command(process)) {
		error("cannot fork to run external filter '%s'", cmd);
		return NULL;
	}

	hashmap_entry_init(entry, strhash(cmd));

	sigchain_push(SIGPIPE, SIG_IGN);

	err = packet_write_list(process->in, "git-filter-client", "version=2", NULL);
	if (err)
		goto done;

	err = strcmp(packet_read_line(process->out, NULL), "git-filter-server");
	if (err) {
		error("external filter '%s' does not support filter protocol version 2", cmd);
		goto done;
	}
	err = strcmp(packet_read_line(process->out, NULL), "version=2");
	if (err)
		goto done;
	err = packet_read_line(process->out, NULL) != NULL;
	if (err)
		goto done;

	err = packet_write_list(process->in, "capability=clean", "capability=smudge", NULL);

	for (;;) {
		cap_buf = packet_read_line(process->out, NULL);
		if (!cap_buf)
			break;
		string_list_split_in_place(&cap_list, cap_buf, '=', 1);

		if (cap_list.nr != 2 || strcmp(cap_list.items[0].string, "capability"))
			continue;

		cap_name = cap_list.items[1].string;
		if (!strcmp(cap_name, "clean")) {
			entry->supported_capabilities |= CAP_CLEAN;
		} else if (!strcmp(cap_name, "smudge")) {
			entry->supported_capabilities |= CAP_SMUDGE;
		} else {
			warning(
				"external filter '%s' requested unsupported filter capability '%s'",
				cmd, cap_name
			);
		}

		string_list_clear(&cap_list, 0);
	}

done:
	sigchain_pop(SIGPIPE);

	if (err || errno == EPIPE) {
		error("initialization for external filter '%s' failed", cmd);
		kill_multi_file_filter(hashmap, entry);
		return NULL;
	}

	hashmap_add(hashmap, entry);
	return entry;
}