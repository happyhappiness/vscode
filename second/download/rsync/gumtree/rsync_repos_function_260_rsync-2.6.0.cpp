void auth_client(int fd, char *user, char *challenge)
{
	char *pass;
	char pass2[30];
	extern char *password_file;

	if (!user || !*user) return;

	if (!(pass=getpassf(password_file)) && !(pass=getenv("RSYNC_PASSWORD"))) {
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

	if (!pass || !*pass) {
		pass = "";
	}

	generate_hash(pass, challenge, pass2);
	io_printf(fd, "%s %s\n", user, pass2);
}