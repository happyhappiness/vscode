	sum_update(input, sizeof input);
	len = sum_end(digest);

	base64_encode(digest, len, challenge, 0);
}


/* Return the secret for a user from the secret file, null terminated.
 * Maximum length is len (not counting the null). */
static int get_secret(int module, const char *user, char *secret, int len)
{
	const char *fname = lp_secrets_file(module);
	STRUCT_STAT st;
	int fd, ok = 1;
	const char *p;
	char ch, *s;

	if (!fname || !*fname)
		return 0;

	if ((fd = open(fname, O_RDONLY)) < 0)
		return 0;

	if (do_stat(fname, &st) == -1) {
		rsyserr(FLOG, errno, "stat(%s)", fname);
		ok = 0;
	} else if (lp_strict_modes(module)) {
		if ((st.st_mode & 06) != 0) {
			rprintf(FLOG, "secrets file must not be other-accessible (see strict modes option)\n");
			ok = 0;
		} else if (MY_UID() == 0 && st.st_uid != 0) {
			rprintf(FLOG, "secrets file must be owned by root when running as root (see strict modes)\n");
			ok = 0;
		}
	}
	if (!ok) {
		rprintf(FLOG, "continuing without secrets file\n");
		close(fd);
		return 0;
	}

	if (*user == '#') {
		/* Reject attempt to match a comment. */
		close(fd);
		return 0;
	}

	/* Try to find a line that starts with the user name and a ':'. */
	p = user;
	while (1) {
		if (read(fd, &ch, 1) != 1) {
			close(fd);
			return 0;
		}
		if (ch == '\n')
			p = user;
		else if (p) {
			if (*p == ch)
				p++;
			else if (!*p && ch == ':')
				break;
			else
				p = NULL;
		}
	}

	/* Slurp the secret into the "secret" buffer. */
	s = secret;
	while (len > 0) {
		if (read(fd, s, 1) != 1 || *s == '\n')
			break;
		if (*s == '\r')
			continue;
		s++;
		len--;
	}
	*s = '\0';
	close(fd);

	return 1;
}

static const char *getpassf(const char *filename)
{
	STRUCT_STAT st;
	char buffer[512], *p;
	int fd, n;

	if (!filename)
		return NULL;

	if ((fd = open(filename,O_RDONLY)) < 0) {
		rsyserr(FERROR, errno, "could not open password file %s", filename);
		exit_cleanup(RERR_SYNTAX);
	}

	if (do_stat(filename, &st) == -1) {
		rsyserr(FERROR, errno, "stat(%s)", filename);
		exit_cleanup(RERR_SYNTAX);
	}
	if ((st.st_mode & 06) != 0) {
		rprintf(FERROR, "ERROR: password file must not be other-accessible\n");
		exit_cleanup(RERR_SYNTAX);
	}
	if (MY_UID() == 0 && st.st_uid != 0) {
		rprintf(FERROR, "ERROR: password file must be owned by root when running as root\n");
		exit_cleanup(RERR_SYNTAX);
	}

	n = read(fd, buffer, sizeof buffer - 1);
	close(fd);
	if (n > 0) {
		buffer[n] = '\0';
		if ((p = strtok(buffer, "\n\r")) != NULL)
			return strdup(p);
	}

	rprintf(FERROR, "ERROR: failed to read a password from %s\n", filename);
	exit_cleanup(RERR_SYNTAX);
}

/* Generate an MD4 hash created from the combination of the password
 * and the challenge string and return it base64-encoded. */
static void generate_hash(const char *in, const char *challenge, char *out)
{
	char buf[MAX_DIGEST_LEN];
	int len;

	sum_init(0);
	sum_update(in, strlen(in));
	sum_update(challenge, strlen(challenge));
	len = sum_end(buf);

	base64_encode(buf, len, out, 0);
}

/* Possibly negotiate authentication with the client.  Use "leader" to
 * start off the auth if necessary.
 *
 * Return NULL if authentication failed.  Return "" if anonymous access.
 * Otherwise return username.
 */
char *auth_server(int f_in, int f_out, int module, const char *host,
		  const char *addr, const char *leader)
{
	char *users = lp_auth_users(module);
	char challenge[MAX_DIGEST_LEN*2];
	char line[BIGPATHBUFLEN];
	char secret[512];
	char pass2[MAX_DIGEST_LEN*2];
	char *tok, *pass;

	/* if no auth list then allow anyone in! */
	if (!users || !*users)
		return "";

	gen_challenge(addr, challenge);

	io_printf(f_out, "%s%s\n", leader, challenge);

	if (!read_line_old(f_in, line, sizeof line)
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

void auth_client(int fd, const char *user, const char *challenge)
{
