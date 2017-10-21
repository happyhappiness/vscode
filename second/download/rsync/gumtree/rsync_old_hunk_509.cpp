	sum_end(buf);

	base64_encode(buf, 16, out);
}

/* possible negotiate authentication with the client. Use "leader" to
   start off the auth if necessary */
int auth_server(int fd, int module, char *addr, char *leader)
{
	char *users = lp_auth_users(module);
	char challenge[16];
	char b64_challenge[30];
	char line[MAXPATHLEN];
	char user[100];
	char secret[100];
	char pass[30];
	char pass2[30];
	char *tok;

	/* if no auth list then allow anyone in! */
	if (!users || !*users) return 1;

	gen_challenge(addr, challenge);
	
	base64_encode(challenge, 16, b64_challenge);

	io_printf(fd,"%s%s\n", leader, b64_challenge);

	if (!read_line(fd, line, sizeof(line)-1)) {
		return 0;
	}

	memset(user, 0, sizeof(user));
	memset(pass, 0, sizeof(pass));

	if (sscanf(line,"%99s %29s", user, pass) != 2) {
		return 0;
	}

	users = strdup(users);
	if (!users) return 0;

	for (tok=strtok(users," ,\t"); tok; tok = strtok(NULL," ,\t")) {
		if (strcmp(tok, user) == 0) break;
	}
	free(users);

	if (!tok) {
		return 0;
	}
	
	memset(secret, 0, sizeof(secret));
	if (!get_secret(module, user, secret, sizeof(secret)-1)) {
		memset(secret, 0, sizeof(secret));
		return 0;
	}

	generate_hash(secret, b64_challenge, pass2);
	memset(secret, 0, sizeof(secret));
	
	return (strcmp(pass, pass2) == 0);
}


void auth_client(int fd, char *user, char *challenge)
{
	char *pass;
