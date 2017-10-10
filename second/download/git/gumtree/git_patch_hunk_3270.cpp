 		struct credential_cache_entry *e = lookup_credential(&c);
 		if (e) {
 			fprintf(out, "username=%s\n", e->item.username);
 			fprintf(out, "password=%s\n", e->item.password);
 		}
 	}
-	else if (!strcmp(action.buf, "exit"))
+	else if (!strcmp(action.buf, "exit")) {
+		/*
+		 * It's important that we clean up our socket first, and then
+		 * signal the client only once we have finished the cleanup.
+		 * Calling exit() directly does this, because we clean up in
+		 * our atexit() handler, and then signal the client when our
+		 * process actually ends, which closes the socket and gives
+		 * them EOF.
+		 */
 		exit(0);
+	}
 	else if (!strcmp(action.buf, "erase"))
 		remove_credential(&c);
 	else if (!strcmp(action.buf, "store")) {
 		if (timeout < 0)
 			warning("cache client didn't specify a timeout");
 		else if (!c.username || !c.password)
