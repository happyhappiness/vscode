
	fflush(NULL);
	if (start_async(&async))
		return 0;	/* error was already reported */

	if (strbuf_read(&nbuf, async.out, len) < 0) {
		err = error("read from external filter '%s' failed", cmd);
	}
	if (close(async.out)) {
		err = error("read from external filter '%s' failed", cmd);
	}
	if (finish_async(&async)) {
		err = error("external filter '%s' failed", cmd);
	}

	if (!err) {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
}

#define CAP_CLEAN    (1u<<0)
#define CAP_SMUDGE   (1u<<1)

struct cmd2process {
	struct hashmap_entry ent; /* must be the first member! */
	unsigned int supported_capabilities;
	const char *cmd;
	struct child_process process;
};

static int cmd_process_map_initialized;
static struct hashmap cmd_process_map;

static int cmd2process_cmp(const struct cmd2process *e1,
			   const struct cmd2process *e2,
			   const void *unused)
{
	return strcmp(e1->cmd, e2->cmd);
}

static struct cmd2process *find_multi_file_filter_entry(struct hashmap *hashmap, const char *cmd)
{
	struct cmd2process key;
	hashmap_entry_init(&key, strhash(cmd));
	key.cmd = cmd;
	return hashmap_get(hashmap, &key, NULL);
}

static int packet_write_list(int fd, const char *line, ...)
{
	va_list args;
	int err;
	va_start(args, line);
	for (;;) {
		if (!line)
			break;
		if (strlen(line) > LARGE_PACKET_DATA_MAX)
			return -1;
		err = packet_write_fmt_gently(fd, "%s\n", line);
		if (err)
			return err;
		line = va_arg(args, const char*);
	}
	va_end(args);
	return packet_flush_gently(fd);
}

static void read_multi_file_filter_status(int fd, struct strbuf *status)
{
	struct strbuf **pair;
	char *line;
	for (;;) {
		line = packet_read_line(fd, NULL);
		if (!line)
			break;
		pair = strbuf_split_str(line, '=', 2);
		if (pair[0] && pair[0]->len && pair[1]) {
			/* the last "status=<foo>" line wins */
			if (!strcmp(pair[0]->buf, "status=")) {
				strbuf_reset(status);
				strbuf_addbuf(status, pair[1]);
			}
		}
		strbuf_list_free(pair);
	}
}

static void kill_multi_file_filter(struct hashmap *hashmap, struct cmd2process *entry)
{
	if (!entry)
		return;

	entry->process.clean_on_exit = 0;
	kill(entry->process.pid, SIGTERM);
	finish_command(&entry->process);

	hashmap_remove(hashmap, entry, NULL);
	free(entry);
}

static void stop_multi_file_filter(struct child_process *process)
{
	sigchain_push(SIGPIPE, SIG_IGN);
	/* Closing the pipe signals the filter to initiate a shutdown. */
	close(process->in);
	close(process->out);
	sigchain_pop(SIGPIPE);
	/* Finish command will wait until the shutdown is complete. */
	finish_command(process);
}

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

static struct convert_driver {
	const char *name;
	struct convert_driver *next;
	const char *smudge;
	const char *clean;
	const char *process;
	int required;
} *user_convert, **user_convert_tail;

static int apply_filter(const char *path, const char *src, size_t len,
			int fd, struct strbuf *dst, struct convert_driver *drv,
			const unsigned int wanted_capability)
{
	const char *cmd = NULL;

	if (!drv)
		return 0;

	if (!dst)
		return 1;

	if ((CAP_CLEAN & wanted_capability) && !drv->process && drv->clean)
		cmd = drv->clean;
	else if ((CAP_SMUDGE & wanted_capability) && !drv->process && drv->smudge)
		cmd = drv->smudge;

	if (cmd && *cmd)
		return apply_single_file_filter(path, src, len, fd, dst, cmd);
	else if (drv->process && *drv->process)
		return apply_multi_file_filter(path, src, len, fd, dst, drv->process, wanted_capability);

	return 0;
}

static int read_convert_config(const char *var, const char *value, void *cb)
{
	const char *key, *name;
	int namelen;
	struct convert_driver *drv;

