 				  cmd->tag, cmd->cmd, cmd->cb.dlen,
 				  CAP(LITERALPLUS) ? "+" : "");
 
 	if (Verbose) {
 		if (imap->num_in_progress)
 			printf("(%d in progress) ", imap->num_in_progress);
-		if (memcmp(cmd->cmd, "LOGIN", 5))
+		if (!starts_with(cmd->cmd, "LOGIN"))
 			printf(">>> %s", buf);
 		else
 			printf(">>> %d LOGIN <user> <pass>\n", cmd->tag);
 	}
 	if (socket_write(&imap->buf.sock, buf, bufl) != bufl) {
 		free(cmd->cmd);
