 			if (!srvc->user)
 				srvc->user = xstrdup(cred.username);
 			if (!srvc->pass)
 				srvc->pass = xstrdup(cred.password);
 		}
 
-		if (CAP(NOLOGIN)) {
-			fprintf(stderr, "Skipping account %s@%s, server forbids LOGIN\n", srvc->user, srvc->host);
-			goto bail;
-		}
-
 		if (srvc->auth_method) {
 			struct imap_cmd_cb cb;
 
 			if (!strcmp(srvc->auth_method, "CRAM-MD5")) {
 				if (!CAP(AUTH_CRAM_MD5)) {
 					fprintf(stderr, "You specified"
