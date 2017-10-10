 	if (!total) {
 		fprintf(stderr, "no messages to send\n");
 		return 1;
 	}
 
 	/* write it to the imap server */
-	ctx = imap_open_store(&server);
+	ctx = imap_open_store(&server, server.folder);
 	if (!ctx) {
 		fprintf(stderr, "failed to open store\n");
 		return 1;
 	}
 
 	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
-	ctx->name = imap_folder;
 	while (1) {
 		unsigned percent = n * 100 / total;
 
 		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);
 		if (!split_msg(&all_msgs, &msg, &ofs))
 			break;
