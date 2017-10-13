int async_query_available_blobs(const char *cmd, struct string_list *available_paths)
{
	int err;
	char *line;
	struct cmd2process *entry;
	struct child_process *process;
	struct strbuf filter_status = STRBUF_INIT;

	assert(subprocess_map_initialized);
	entry = (struct cmd2process *)subprocess_find_entry(&subprocess_map, cmd);
	if (!entry) {
		error("external filter '%s' is not available anymore although "
		      "not all paths have been filtered", cmd);
		return 0;
	}
	process = &entry->subprocess.process;
	sigchain_push(SIGPIPE, SIG_IGN);

	err = packet_write_fmt_gently(
		process->in, "command=list_available_blobs\n");
	if (err)
		goto done;

	err = packet_flush_gently(process->in);
	if (err)
		goto done;

	while ((line = packet_read_line(process->out, NULL))) {
		const char *path;
		if (skip_prefix(line, "pathname=", &path))
			string_list_insert(available_paths, xstrdup(path));
		else
			; /* ignore unknown keys */
	}

	err = subprocess_read_status(process->out, &filter_status);
	if (err)
		goto done;

	err = strcmp(filter_status.buf, "success");

done:
	sigchain_pop(SIGPIPE);

	if (err)
		handle_filter_error(&filter_status, entry, 0);
	return !err;
}