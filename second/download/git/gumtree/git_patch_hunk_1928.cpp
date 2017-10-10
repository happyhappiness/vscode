 
 static int rsync_transport_push(struct transport *transport,
 		int refspec_nr, const char **refspec, int flags)
 {
 	struct strbuf buf = STRBUF_INIT, temp_dir = STRBUF_INIT;
 	int result = 0, i;
-	struct child_process rsync;
+	struct child_process rsync = CHILD_PROCESS_INIT;
 	const char *args[10];
 
 	if (flags & TRANSPORT_PUSH_MIRROR)
 		return error("rsync transport does not support mirror mode");
 
 	/* first push the objects */
 
 	strbuf_addstr(&buf, rsync_url(transport->url));
 	strbuf_addch(&buf, '/');
 
-	memset(&rsync, 0, sizeof(rsync));
 	rsync.argv = args;
 	rsync.stdout_to_stderr = 1;
 	i = 0;
 	args[i++] = "rsync";
 	args[i++] = "-a";
 	if (flags & TRANSPORT_PUSH_DRY_RUN)
