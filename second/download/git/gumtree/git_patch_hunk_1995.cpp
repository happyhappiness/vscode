 		bufl = nfsnprintf(buf, sizeof(buf), "%d %s\r\n", cmd->tag, cmd->cmd);
 	else
 		bufl = nfsnprintf(buf, sizeof(buf), "%d %s{%d%s}\r\n",
 				  cmd->tag, cmd->cmd, cmd->cb.dlen,
 				  CAP(LITERALPLUS) ? "+" : "");
 
-	if (Verbose) {
+	if (0 < verbosity) {
 		if (imap->num_in_progress)
 			printf("(%d in progress) ", imap->num_in_progress);
 		if (!starts_with(cmd->cmd, "LOGIN"))
 			printf(">>> %s", buf);
 		else
 			printf(">>> %d LOGIN <user> <pass>\n", cmd->tag);
