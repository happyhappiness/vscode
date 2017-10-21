char *auth_server(int f_in, int f_out, int module, char *host, char *addr,
		  char *leader)
{
	char *users = lp_auth_users(module);
	char challenge[MD4_SUM_LENGTH*2];
	char line[MAXPATHLEN];
	char secret[512];
	char pass2[MD4_SUM_LENGTH*2];
	char *tok, *pass;

	/* if no auth list then allow anyone in! */
	if (!users || !*users)
		return "";

	gen_challenge(addr, challenge);

	io_printf(f_out, "%s%s\n", leader, challenge);

	if (!read_line(f_in, line, sizeof line - 1)
	 || (pass = strchr(line, ' ')) == NULL) {
		rprintf(FLOG, "auth failed on module %s from %s (%s): "
			"invalid challenge response\n",
			lp_name(module), host, addr);
		return NULL;
	}
	*pass++ = '\0';

	if (!(users = strdup(users)))
		out_of_memory("auth_server");

	for (tok = strtok(users, " ,\t"); tok; tok = strtok(NULL, " ,\t")) {
		if (wildmatch(tok, line))
			break;
	}
	free(users);

	if (!tok) {
		rprintf(FLOG, "auth failed on module %s from %s (%s): "
			"unauthorized user\n",
			lp_name(module), host, addr);
		return NULL;
	}

	memset(secret, 0, sizeof secret);
	if (!get_secret(module, line, secret, sizeof secret - 1)) {
		memset(secret, 0, sizeof secret);
		rprintf(FLOG, "auth failed on module %s from %s (%s): "
			"missing secret for user \"%s\"\n",
			lp_name(module), host, addr, line);
		return NULL;
	}

	generate_hash(secret, challenge, pass2);
	memset(secret, 0, sizeof secret);

	if (strcmp(pass, pass2) != 0) {
		rprintf(FLOG, "auth failed on module %s from %s (%s): "
			"password mismatch\n",
			lp_name(module), host, addr);
		return NULL;
	}

	return strdup(line);
}