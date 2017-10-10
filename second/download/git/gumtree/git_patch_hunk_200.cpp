 			/* capabilities may have changed, so get the new capabilities */
 			if (imap_exec(ctx, NULL, "CAPABILITY") != RESP_OK)
 				goto bail;
 		}
 #endif
 		imap_info("Logging in...\n");
-		if (!srvc->user) {
-			fprintf(stderr, "Skipping server %s, no user\n", srvc->host);
-			goto bail;
-		}
-		if (!srvc->pass) {
-			struct strbuf prompt = STRBUF_INIT;
-			strbuf_addf(&prompt, "Password (%s@%s): ", srvc->user, srvc->host);
-			arg = git_getpass(prompt.buf);
-			strbuf_release(&prompt);
-			if (!*arg) {
-				fprintf(stderr, "Skipping account %s@%s, no password\n", srvc->user, srvc->host);
-				goto bail;
-			}
-			/*
-			 * getpass() returns a pointer to a static buffer.  make a copy
-			 * for long term storage.
-			 */
-			srvc->pass = xstrdup(arg);
+		if (!srvc->user || !srvc->pass) {
+			cred.protocol = xstrdup(srvc->use_ssl ? "imaps" : "imap");
+			cred.host = xstrdup(srvc->host);
+
+			if (srvc->user)
+				cred.username = xstrdup(srvc->user);
+			if (srvc->pass)
+				cred.password = xstrdup(srvc->pass);
+
+			credential_fill(&cred);
+
+			if (!srvc->user)
+				srvc->user = xstrdup(cred.username);
+			if (!srvc->pass)
+				srvc->pass = xstrdup(cred.password);
 		}
+
 		if (CAP(NOLOGIN)) {
 			fprintf(stderr, "Skipping account %s@%s, server forbids LOGIN\n", srvc->user, srvc->host);
 			goto bail;
 		}
 
 		if (srvc->auth_method) {
