			return strdup(p);
	}

	return NULL;
}

/* generate a 16 byte hash from a password and challenge */
static void generate_hash(char *in, char *challenge, char *out)
{
	char buf[16];

	sum_init(0);
	sum_update(in, strlen(in));
	sum_update(challenge, strlen(challenge));
	sum_end(buf);

	base64_encode(buf, 16, out);
}

/* Possibly negotiate authentication with the client.  Use "leader" to
 * start off the auth if necessary.
 *
 * Return NULL if authentication failed.  Return "" if anonymous access.
 * Otherwise return username.
 */
char *auth_server(int f_in, int f_out, int module, char *addr, char *leader)
{
	char *users = lp_auth_users(module);
	char challenge[16];
	char b64_challenge[30];
	char line[MAXPATHLEN];
	static char user[100];
	char secret[100];
	char pass[30];
	char pass2[30];
	char *tok;

	/* if no auth list then allow anyone in! */
	if (!users || !*users)
		return "";

	gen_challenge(addr, challenge);

	base64_encode(challenge, 16, b64_challenge);

	io_printf(f_out, "%s%s\n", leader, b64_challenge);

	if (!read_line(f_in, line, sizeof line - 1))
		return NULL;

	memset(user, 0, sizeof user);
	memset(pass, 0, sizeof pass);

	if (sscanf(line,"%99s %29s", user, pass) != 2)
		return NULL;

	users = strdup(users);
	if (!users)
		return NULL;

	for (tok=strtok(users," ,\t"); tok; tok = strtok(NULL," ,\t")) {
		if (wildmatch(tok, user))
			break;
	}
	free(users);

	if (!tok)
		return NULL;

	memset(secret, 0, sizeof secret);
	if (!get_secret(module, user, secret, sizeof secret - 1)) {
		memset(secret, 0, sizeof secret);
		return NULL;
	}

	generate_hash(secret, b64_challenge, pass2);
	memset(secret, 0, sizeof secret);

	if (strcmp(pass, pass2) == 0)
		return user;

	return NULL;
}


void auth_client(int fd, char *user, char *challenge)
{
	char *pass;
	char pass2[30];

	if (!user || !*user)
		user = "nobody";

	if (!(pass = getpassf(password_file))
	 && !(pass = getenv("RSYNC_PASSWORD"))) {
