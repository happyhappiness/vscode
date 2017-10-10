 }
 
 #define CAP_CLEAN    (1u<<0)
 #define CAP_SMUDGE   (1u<<1)
 
 struct cmd2process {
-	struct hashmap_entry ent; /* must be the first member! */
+	struct subprocess_entry subprocess; /* must be the first member! */
 	unsigned int supported_capabilities;
-	const char *cmd;
-	struct child_process process;
 };
 
-static int cmd_process_map_initialized;
-static struct hashmap cmd_process_map;
-
-static int cmd2process_cmp(const struct cmd2process *e1,
-			   const struct cmd2process *e2,
-			   const void *unused)
-{
-	return strcmp(e1->cmd, e2->cmd);
-}
-
-static struct cmd2process *find_multi_file_filter_entry(struct hashmap *hashmap, const char *cmd)
-{
-	struct cmd2process key;
-	hashmap_entry_init(&key, strhash(cmd));
-	key.cmd = cmd;
-	return hashmap_get(hashmap, &key, NULL);
-}
+static int subprocess_map_initialized;
+static struct hashmap subprocess_map;
 
-static int packet_write_list(int fd, const char *line, ...)
+static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
 {
-	va_list args;
 	int err;
-	va_start(args, line);
-	for (;;) {
-		if (!line)
-			break;
-		if (strlen(line) > LARGE_PACKET_DATA_MAX)
-			return -1;
-		err = packet_write_fmt_gently(fd, "%s\n", line);
-		if (err)
-			return err;
-		line = va_arg(args, const char*);
-	}
-	va_end(args);
-	return packet_flush_gently(fd);
-}
-
-static void read_multi_file_filter_status(int fd, struct strbuf *status)
-{
-	struct strbuf **pair;
-	char *line;
-	for (;;) {
-		line = packet_read_line(fd, NULL);
-		if (!line)
-			break;
-		pair = strbuf_split_str(line, '=', 2);
-		if (pair[0] && pair[0]->len && pair[1]) {
-			/* the last "status=<foo>" line wins */
-			if (!strcmp(pair[0]->buf, "status=")) {
-				strbuf_reset(status);
-				strbuf_addbuf(status, pair[1]);
-			}
-		}
-		strbuf_list_free(pair);
-	}
-}
-
-static void kill_multi_file_filter(struct hashmap *hashmap, struct cmd2process *entry)
-{
-	if (!entry)
-		return;
-
-	entry->process.clean_on_exit = 0;
-	kill(entry->process.pid, SIGTERM);
-	finish_command(&entry->process);
-
-	hashmap_remove(hashmap, entry, NULL);
-	free(entry);
-}
-
-static void stop_multi_file_filter(struct child_process *process)
-{
-	sigchain_push(SIGPIPE, SIG_IGN);
-	/* Closing the pipe signals the filter to initiate a shutdown. */
-	close(process->in);
-	close(process->out);
-	sigchain_pop(SIGPIPE);
-	/* Finish command will wait until the shutdown is complete. */
-	finish_command(process);
-}
-
-static struct cmd2process *start_multi_file_filter(struct hashmap *hashmap, const char *cmd)
-{
-	int err;
-	struct cmd2process *entry;
-	struct child_process *process;
-	const char *argv[] = { cmd, NULL };
+	struct cmd2process *entry = (struct cmd2process *)subprocess;
 	struct string_list cap_list = STRING_LIST_INIT_NODUP;
 	char *cap_buf;
 	const char *cap_name;
-
-	entry = xmalloc(sizeof(*entry));
-	entry->cmd = cmd;
-	entry->supported_capabilities = 0;
-	process = &entry->process;
-
-	child_process_init(process);
-	process->argv = argv;
-	process->use_shell = 1;
-	process->in = -1;
-	process->out = -1;
-	process->clean_on_exit = 1;
-	process->clean_on_exit_handler = stop_multi_file_filter;
-
-	if (start_command(process)) {
-		error("cannot fork to run external filter '%s'", cmd);
-		return NULL;
-	}
-
-	hashmap_entry_init(entry, strhash(cmd));
+	struct child_process *process = &subprocess->process;
+	const char *cmd = subprocess->cmd;
 
 	sigchain_push(SIGPIPE, SIG_IGN);
 
-	err = packet_write_list(process->in, "git-filter-client", "version=2", NULL);
+	err = packet_writel(process->in, "git-filter-client", "version=2", NULL);
 	if (err)
 		goto done;
 
 	err = strcmp(packet_read_line(process->out, NULL), "git-filter-server");
 	if (err) {
 		error("external filter '%s' does not support filter protocol version 2", cmd);
