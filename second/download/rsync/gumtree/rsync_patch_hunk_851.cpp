 
 	return NULL;
 }
 
 /* Generate an MD4 hash created from the combination of the password
  * and the challenge string and return it base64-encoded. */
-static void generate_hash(char *in, char *challenge, char *out)
+static void generate_hash(const char *in, const char *challenge, char *out)
 {
-	char buf[MD4_SUM_LENGTH];
+	char buf[MAX_DIGEST_LEN];
+	int len;
 
 	sum_init(0);
 	sum_update(in, strlen(in));
 	sum_update(challenge, strlen(challenge));
-	sum_end(buf);
+	len = sum_end(buf);
 
-	base64_encode(buf, MD4_SUM_LENGTH, out, 0);
+	base64_encode(buf, len, out, 0);
 }
 
 /* Possibly negotiate authentication with the client.  Use "leader" to
  * start off the auth if necessary.
  *
  * Return NULL if authentication failed.  Return "" if anonymous access.
  * Otherwise return username.
  */
-char *auth_server(int f_in, int f_out, int module, char *host, char *addr,
-		  char *leader)
+char *auth_server(int f_in, int f_out, int module, const char *host,
+		  const char *addr, const char *leader)
 {
 	char *users = lp_auth_users(module);
-	char challenge[MD4_SUM_LENGTH*2];
+	char challenge[MAX_DIGEST_LEN*2];
 	char line[BIGPATHBUFLEN];
 	char secret[512];
-	char pass2[MD4_SUM_LENGTH*2];
+	char pass2[MAX_DIGEST_LEN*2];
 	char *tok, *pass;
 
 	/* if no auth list then allow anyone in! */
 	if (!users || !*users)
 		return "";
 
 	gen_challenge(addr, challenge);
 
 	io_printf(f_out, "%s%s\n", leader, challenge);
 
-	if (!read_line(f_in, line, sizeof line - 1)
+	if (!read_line_old(f_in, line, sizeof line)
 	 || (pass = strchr(line, ' ')) == NULL) {
 		rprintf(FLOG, "auth failed on module %s from %s (%s): "
 			"invalid challenge response\n",
 			lp_name(module), host, addr);
 		return NULL;
 	}
