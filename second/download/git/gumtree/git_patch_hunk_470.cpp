 	}
 
 	if (is_repository_shallow())
 		write_shallow_commits(&req_buf, 1, NULL);
 	if (args->depth > 0)
 		packet_buf_write(&req_buf, "deepen %d", args->depth);
+	if (args->deepen_since) {
+		unsigned long max_age = approxidate(args->deepen_since);
+		packet_buf_write(&req_buf, "deepen-since %lu", max_age);
+	}
+	if (args->deepen_not) {
+		int i;
+		for (i = 0; i < args->deepen_not->nr; i++) {
+			struct string_list_item *s = args->deepen_not->items + i;
+			packet_buf_write(&req_buf, "deepen-not %s", s->string);
+		}
+	}
 	packet_buf_flush(&req_buf);
 	state_len = req_buf.len;
 
-	if (args->depth > 0) {
+	if (args->deepen) {
 		char *line;
 		const char *arg;
 		unsigned char sha1[20];
 
 		send_request(args, fd[1], &req_buf);
 		while ((line = packet_read_line(fd[0], NULL))) {
 			if (skip_prefix(line, "shallow ", &arg)) {
 				if (get_sha1_hex(arg, sha1))
-					die("invalid shallow line: %s", line);
+					die(_("invalid shallow line: %s"), line);
 				register_shallow(sha1);
 				continue;
 			}
 			if (skip_prefix(line, "unshallow ", &arg)) {
 				if (get_sha1_hex(arg, sha1))
-					die("invalid unshallow line: %s", line);
+					die(_("invalid unshallow line: %s"), line);
 				if (!lookup_object(sha1))
-					die("object not found: %s", line);
+					die(_("object not found: %s"), line);
 				/* make sure that it is parsed as shallow */
 				if (!parse_object(sha1))
-					die("error in object: %s", line);
+					die(_("error in object: %s"), line);
 				if (unregister_shallow(sha1))
-					die("no shallow found: %s", line);
+					die(_("no shallow found: %s"), line);
 				continue;
 			}
-			die("expected shallow/unshallow, got %s", line);
+			die(_("expected shallow/unshallow, got %s"), line);
 		}
 	} else if (!args->stateless_rpc)
 		send_request(args, fd[1], &req_buf);
 
 	if (!args->stateless_rpc) {
 		/* If we aren't using the stateless-rpc interface
