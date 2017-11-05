static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
{
	int err;
	struct cmd2process *entry = (struct cmd2process *)subprocess;
	struct string_list cap_list = STRING_LIST_INIT_NODUP;
	char *cap_buf;
	const char *cap_name;
	struct child_process *process = &subprocess->process;
	const char *cmd = subprocess->cmd;

	sigchain_push(SIGPIPE, SIG_IGN);

	err = packet_writel(process->in, "git-filter-client", "version=2", NULL);
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

	err = packet_writel(process->in, "capability=clean", "capability=smudge", NULL);

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

	return err;
}