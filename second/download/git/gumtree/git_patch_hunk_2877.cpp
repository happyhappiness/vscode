 	return ret;
 }
 
 static void send_git_request(int stdin_fd, const char *serv, const char *repo,
 	const char *vhost)
 {
-	size_t bufferspace;
-	size_t wpos = 0;
-	char *buffer;
-
-	/*
-	 * Request needs 12 bytes extra if there is vhost (xxxx \0host=\0) and
-	 * 6 bytes extra (xxxx \0) if there is no vhost.
-	 */
-	if (vhost)
-		bufferspace = strlen(serv) + strlen(repo) + strlen(vhost) + 12;
+	if (!vhost)
+		packet_write(stdin_fd, "%s %s%c", serv, repo, 0);
 	else
-		bufferspace = strlen(serv) + strlen(repo) + 6;
-
-	if (bufferspace > 0xFFFF)
-		die("Request too large to send");
-	buffer = xmalloc(bufferspace);
-
-	/* Make the packet. */
-	wpos = sprintf(buffer, "%04x%s %s%c", (unsigned)bufferspace,
-		serv, repo, 0);
-
-	/* Add vhost if any. */
-	if (vhost)
-		sprintf(buffer + wpos, "host=%s%c", vhost, 0);
-
-	/* Send the request */
-	if (write_in_full(stdin_fd, buffer, bufferspace) < 0)
-		die_errno("Failed to send request");
-
-	free(buffer);
+		packet_write(stdin_fd, "%s %s%chost=%s%c", serv, repo, 0,
+			     vhost, 0);
 }
 
 static int run_child(const char *arg, const char *service)
 {
 	int r;
 	struct child_process child = CHILD_PROCESS_INIT;
