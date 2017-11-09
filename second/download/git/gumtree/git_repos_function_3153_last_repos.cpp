static int apply_multi_file_filter(const char *path, const char *src, size_t len,
				   int fd, struct strbuf *dst, const char *cmd,
				   const unsigned int wanted_capability,
				   struct delayed_checkout *dco)
{
	int err;
	int can_delay = 0;
	struct cmd2process *entry;
	struct child_process *process;
	struct strbuf nbuf = STRBUF_INIT;
	struct strbuf filter_status = STRBUF_INIT;
	const char *filter_type;

	if (!subprocess_map_initialized) {
		subprocess_map_initialized = 1;
		hashmap_init(&subprocess_map, (hashmap_cmp_fn) cmd2process_cmp,
			     NULL, 0);
		entry = NULL;
	} else {
		entry = (struct cmd2process *)subprocess_find_entry(&subprocess_map, cmd);
	}

	fflush(NULL);

	if (!entry) {
		entry = xmalloc(sizeof(*entry));
		entry->supported_capabilities = 0;

		if (subprocess_start(&subprocess_map, &entry->subprocess, cmd, start_multi_file_filter_fn)) {
			free(entry);
			return 0;
		}
	}
	process = &entry->subprocess.process;

	if (!(entry->supported_capabilities & wanted_capability))
		return 0;

	if (wanted_capability & CAP_CLEAN)
		filter_type = "clean";
	else if (wanted_capability & CAP_SMUDGE)
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

	if ((entry->supported_capabilities & CAP_DELAY) &&
	    dco && dco->state == CE_CAN_DELAY) {
		can_delay = 1;
		err = packet_write_fmt_gently(process->in, "can-delay=1\n");
		if (err)
			goto done;
	}

	err = packet_flush_gently(process->in);
	if (err)
		goto done;

	if (fd >= 0)
		err = write_packetized_from_fd(fd, process->in);
	else
		err = write_packetized_from_buf(src, len, process->in);
	if (err)
		goto done;

	err = subprocess_read_status(process->out, &filter_status);
	if (err)
		goto done;

	if (can_delay && !strcmp(filter_status.buf, "delayed")) {
		string_list_insert(&dco->filters, cmd);
		string_list_insert(&dco->paths, path);
	} else {
		/* The filter got the blob and wants to send us a response. */
		err = strcmp(filter_status.buf, "success");
		if (err)
			goto done;

		err = read_packetized_to_strbuf(process->out, &nbuf) < 0;
		if (err)
			goto done;

		err = subprocess_read_status(process->out, &filter_status);
		if (err)
			goto done;

		err = strcmp(filter_status.buf, "success");
	}

done:
	sigchain_pop(SIGPIPE);

	if (err)
		handle_filter_error(&filter_status, entry, wanted_capability);
	else
		strbuf_swap(dst, &nbuf);
	strbuf_release(&nbuf);
	return !err;
}