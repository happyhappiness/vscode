 	char secret[100];
 	char pass[30];
 	char pass2[30];
 	char *tok;
 
 	/* if no auth list then allow anyone in! */
-	if (!users || !*users) return "";
+	if (!users || !*users)
+		return "";
 
 	gen_challenge(addr, challenge);
-	
+
 	base64_encode(challenge, 16, b64_challenge);
 
 	io_printf(f_out, "%s%s\n", leader, b64_challenge);
 
-	if (!read_line(f_in, line, sizeof(line)-1)) {
+	if (!read_line(f_in, line, sizeof line - 1))
 		return NULL;
-	}
 
-	memset(user, 0, sizeof(user));
-	memset(pass, 0, sizeof(pass));
+	memset(user, 0, sizeof user);
+	memset(pass, 0, sizeof pass);
 
-	if (sscanf(line,"%99s %29s", user, pass) != 2) {
+	if (sscanf(line,"%99s %29s", user, pass) != 2)
 		return NULL;
-	}
-	
+
 	users = strdup(users);
-	if (!users) return NULL;
+	if (!users)
+		return NULL;
 
 	for (tok=strtok(users," ,\t"); tok; tok = strtok(NULL," ,\t")) {
-		if (wildmatch(tok, user)) break;
+		if (wildmatch(tok, user))
+			break;
 	}
 	free(users);
 
-	if (!tok) {
+	if (!tok)
 		return NULL;
-	}
-	
-	memset(secret, 0, sizeof(secret));
-	if (!get_secret(module, user, secret, sizeof(secret)-1)) {
-		memset(secret, 0, sizeof(secret));
+
+	memset(secret, 0, sizeof secret);
+	if (!get_secret(module, user, secret, sizeof secret - 1)) {
+		memset(secret, 0, sizeof secret);
 		return NULL;
 	}
 
 	generate_hash(secret, b64_challenge, pass2);
-	memset(secret, 0, sizeof(secret));
-	
+	memset(secret, 0, sizeof secret);
+
 	if (strcmp(pass, pass2) == 0)
 		return user;
 
 	return NULL;
 }
 
 
 void auth_client(int fd, char *user, char *challenge)
 {
 	char *pass;
 	char pass2[30];
-	extern char *password_file;
 
 	if (!user || !*user)
 		user = "nobody";
 
-	if (!(pass=getpassf(password_file)) && !(pass=getenv("RSYNC_PASSWORD"))) {
+	if (!(pass = getpassf(password_file))
+	 && !(pass = getenv("RSYNC_PASSWORD"))) {
 		/* XXX: cyeoh says that getpass is deprecated, because
 		 * it may return a truncated password on some systems,
 		 * and it is not in the LSB.
                  *
                  * Andrew Klein says that getpassphrase() is present
                  * on Solaris and reads up to 256 characters.
                  *
                  * OpenBSD has a readpassphrase() that might be more suitable.
                  */
 		pass = getpass("Password: ");
 	}
 
-	if (!pass || !*pass) {
+	if (!pass)
 		pass = "";
-	}
 
 	generate_hash(pass, challenge, pass2);
 	io_printf(fd, "%s %s\n", user, pass2);
 }
 
 
