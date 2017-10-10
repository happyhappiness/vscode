 		goto done;
 
 	err = subprocess_read_status(process->out, &filter_status);
 	if (err)
 		goto done;
 
-	err = strcmp(filter_status.buf, "success");
+	if (can_delay && !strcmp(filter_status.buf, "delayed")) {
+		string_list_insert(&dco->filters, cmd);
+		string_list_insert(&dco->paths, path);
+	} else {
+		/* The filter got the blob and wants to send us a response. */
+		err = strcmp(filter_status.buf, "success");
+		if (err)
+			goto done;
+
+		err = read_packetized_to_strbuf(process->out, &nbuf) < 0;
+		if (err)
+			goto done;
+
+		err = subprocess_read_status(process->out, &filter_status);
+		if (err)
+			goto done;
+
+		err = strcmp(filter_status.buf, "success");
+	}
+
+done:
+	sigchain_pop(SIGPIPE);
+
+	if (err)
+		handle_filter_error(&filter_status, entry, wanted_capability);
+	else
+		strbuf_swap(dst, &nbuf);
+	strbuf_release(&nbuf);
+	return !err;
+}
+
+
+int async_query_available_blobs(const char *cmd, struct string_list *available_paths)
+{
+	int err;
+	char *line;
+	struct cmd2process *entry;
+	struct child_process *process;
+	struct strbuf filter_status = STRBUF_INIT;
+
+	assert(subprocess_map_initialized);
+	entry = (struct cmd2process *)subprocess_find_entry(&subprocess_map, cmd);
+	if (!entry) {
+		error("external filter '%s' is not available anymore although "
+		      "not all paths have been filtered", cmd);
+		return 0;
+	}
+	process = &entry->subprocess.process;
+	sigchain_push(SIGPIPE, SIG_IGN);
+
+	err = packet_write_fmt_gently(
+		process->in, "command=list_available_blobs\n");
 	if (err)
 		goto done;
 
-	err = read_packetized_to_strbuf(process->out, &nbuf) < 0;
+	err = packet_flush_gently(process->in);
 	if (err)
 		goto done;
 
+	while ((line = packet_read_line(process->out, NULL))) {
+		const char *path;
+		if (skip_prefix(line, "pathname=", &path))
+			string_list_insert(available_paths, xstrdup(path));
+		else
+			; /* ignore unknown keys */
+	}
+
 	err = subprocess_read_status(process->out, &filter_status);
 	if (err)
 		goto done;
 
 	err = strcmp(filter_status.buf, "success");
 
 done:
 	sigchain_pop(SIGPIPE);
 
-	if (err) {
-		if (!strcmp(filter_status.buf, "error")) {
-			/* The filter signaled a problem with the file. */
-		} else if (!strcmp(filter_status.buf, "abort")) {
-			/*
-			 * The filter signaled a permanent problem. Don't try to filter
-			 * files with the same command for the lifetime of the current
-			 * Git process.
-			 */
-			 entry->supported_capabilities &= ~wanted_capability;
-		} else {
-			/*
-			 * Something went wrong with the protocol filter.
-			 * Force shutdown and restart if another blob requires filtering.
-			 */
-			error("external filter '%s' failed", cmd);
-			subprocess_stop(&subprocess_map, &entry->subprocess);
-			free(entry);
-		}
-	} else {
-		strbuf_swap(dst, &nbuf);
-	}
-	strbuf_release(&nbuf);
+	if (err)
+		handle_filter_error(&filter_status, entry, 0);
 	return !err;
 }
 
 static struct convert_driver {
 	const char *name;
 	struct convert_driver *next;
