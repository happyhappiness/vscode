static int apply_multi_file_filter(const char *path, const char *src, size_t len,
				   int fd, struct strbuf *dst, const char *cmd,
				   const unsigned int wanted_capability)
{
	int err;
	struct cmd2process *entry;
	struct child_process *process;
	struct strbuf nbuf = STRBUF_INIT;
	struct strbuf filter_status = STRBUF_INIT;
	const char *filter_type;

	if (!cmd_process_map_initialized) {
		cmd_process_map_initialized = 1;
		hashmap_init(&cmd_process_map, (hashmap_cmp_fn) cmd2process_cmp, 0);
		entry = NULL;
	} else {
		entry = find_multi_file_filter_entry(&cmd_process_map, cmd);
	}

	fflush(NULL);

	if (!entry) {
		entry = start_multi_file_filter(&cmd_process_map, cmd);
		if (!entry)
			return 0;
	}
	process = &entry->process;

	if (!(wanted_capability & entry->supported_capabilities))
		return 0;

	if (CAP_CLEAN & wanted_capability)
		filter_type = "clean";
	else if (CAP_SMUDGE & wanted_capability)
		filter_type = "smudge";
	else
		die("unexpected filter type");

	sigchain_push(SIGPIPE, SIG_IGN);

	assert(strlen(filter_type) < LARGE_PACKET_DATA_MAX - strlen("command=\n"));
	err = packet_write_fmt_gently(process->in, "command=%s\n", filter_type);
	if (err)
		goto done;

	err = strlen(path) > LARGE_PACKET_DATA_MAX - strlen("pathname=\n");
	if (err) {
		error("path name too long for external filter");
		goto done;
	}

	err = packet_write_fmt_gently(process->in, "pathname=%s\n", path);
	if (err)
		goto done;

	err = packet_flush_gently(process->in);
	if (err)
		goto done;

	if (fd >= 0)
		err = write_packetized_from_fd(fd, process->in);
	else
		err = write_packetized_from_buf(src, len, process->in);
	if (err)
		goto done;

	read_multi_file_filter_status(process->out, &filter_status);
	err = strcmp(filter_status.buf, "success");
	if (err)
		goto done;

	err = read_packetized_to_strbuf(process->out, &nbuf) < 0;
	if (err)
		goto done;

	read_multi_file_filter_status(process->out, &filter_status);
	err = strcmp(filter_status.buf, "success");

done:
	sigchain_pop(SIGPIPE);

	if (err || errno == EPIPE) {
		if (!strcmp(filter_status.buf, "error")) {
			/* The filter signaled a problem with the file. */
		} else if (!strcmp(filter_status.buf, "abort")) {
			/*
			 * The filter signaled a permanent problem. Don't try to filter
			 * files with the same command for the lifetime of the current
			 * Git process.
			 */
			 entry->supported_capabilities &= ~wanted_capability;
		} else {
			/*
			 * Something went wrong with the protocol filter.
			 * Force shutdown and restart if another blob requires filtering.
			 */
			error("external filter '%s' failed", cmd);
			kill_multi_file_filter(&cmd_process_map, entry);
		}
	} else {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
}