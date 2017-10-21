 			return strdup(p);
 	}
 
 	return NULL;
 }
 
-/* generate a 16 byte hash from a password and challenge */
+/* Generate an MD4 hash created from the combination of the password
+ * and the challenge string and return it base64-encoded. */
 static void generate_hash(char *in, char *challenge, char *out)
 {
-	char buf[16];
+	char buf[MD4_SUM_LENGTH];
 
 	sum_init(0);
 	sum_update(in, strlen(in));
 	sum_update(challenge, strlen(challenge));
 	sum_end(buf);
 
-	base64_encode(buf, 16, out);
+	base64_encode(buf, MD4_SUM_LENGTH, out);
 }
 
 /* Possibly negotiate authentication with the client.  Use "leader" to
  * start off the auth if necessary.
  *
  * Return NULL if authentication failed.  Return "" if anonymous access.
  * Otherwise return username.
  */
-char *auth_server(int f_in, int f_out, int module, char *addr, char *leader)
+char *auth_server(int f_in, int f_out, int module, char *host, char *addr,
+		  char *leader)
 {
 	char *users = lp_auth_users(module);
-	char challenge[16];
-	char b64_challenge[30];
+	char challenge[MD4_SUM_LENGTH*2];
 	char line[MAXPATHLEN];
-	static char user[100];
-	char secret[100];
-	char pass[30];
-	char pass2[30];
-	char *tok;
+	char secret[512];
+	char pass2[MD4_SUM_LENGTH*2];
+	char *tok, *pass;
 
 	/* if no auth list then allow anyone in! */
 	if (!users || !*users)
 		return "";
 
 	gen_challenge(addr, challenge);
 
-	base64_encode(challenge, 16, b64_challenge);
-
-	io_printf(f_out, "%s%s\n", leader, b64_challenge);
+	io_printf(f_out, "%s%s\n", leader, challenge);
 
-	if (!read_line(f_in, line, sizeof line - 1))
-		return NULL;
-
-	memset(user, 0, sizeof user);
-	memset(pass, 0, sizeof pass);
-
-	if (sscanf(line,"%99s %29s", user, pass) != 2)
+	if (!read_line(f_in, line, sizeof line - 1)
+	 || (pass = strchr(line, ' ')) == NULL) {
+		rprintf(FLOG, "auth failed on module %s from %s (%s): "
+			"invalid challenge response\n",
+			lp_name(module), host, addr);
 		return NULL;
+	}
+	*pass++ = '\0';
 
-	users = strdup(users);
-	if (!users)
-		return NULL;
+	if (!(users = strdup(users)))
+		out_of_memory("auth_server");
 
-	for (tok=strtok(users," ,\t"); tok; tok = strtok(NULL," ,\t")) {
-		if (wildmatch(tok, user))
+	for (tok = strtok(users, " ,\t"); tok; tok = strtok(NULL, " ,\t")) {
+		if (wildmatch(tok, line))
 			break;
 	}
 	free(users);
 
-	if (!tok)
+	if (!tok) {
+		rprintf(FLOG, "auth failed on module %s from %s (%s): "
+			"unauthorized user\n",
+			lp_name(module), host, addr);
 		return NULL;
+	}
 
 	memset(secret, 0, sizeof secret);
-	if (!get_secret(module, user, secret, sizeof secret - 1)) {
+	if (!get_secret(module, line, secret, sizeof secret - 1)) {
 		memset(secret, 0, sizeof secret);
+		rprintf(FLOG, "auth failed on module %s from %s (%s): "
+			"missing secret for user \"%s\"\n",
+			lp_name(module), host, addr, line);
 		return NULL;
 	}
 
-	generate_hash(secret, b64_challenge, pass2);
+	generate_hash(secret, challenge, pass2);
 	memset(secret, 0, sizeof secret);
 
-	if (strcmp(pass, pass2) == 0)
-		return user;
+	if (strcmp(pass, pass2) != 0) {
+		rprintf(FLOG, "auth failed on module %s from %s (%s): "
+			"password mismatch\n",
+			lp_name(module), host, addr);
+		return NULL;
+	}
 
-	return NULL;
+	return strdup(line);
 }
 
 
 void auth_client(int fd, char *user, char *challenge)
 {
 	char *pass;
-	char pass2[30];
+	char pass2[MD4_SUM_LENGTH*2];
 
 	if (!user || !*user)
 		user = "nobody";
 
 	if (!(pass = getpassf(password_file))
 	 && !(pass = getenv("RSYNC_PASSWORD"))) {
