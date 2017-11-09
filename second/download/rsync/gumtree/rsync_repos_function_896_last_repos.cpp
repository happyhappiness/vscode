char *getpass(const char *prompt)
{
	static char password[256];

	BOOL tty_changed = False, read_success;
	struct termios tty_old, tty_new;
	FILE *in = stdin, *out = stderr;
	FILE *tty = fopen("/dev/tty", "w+");

	if (tty)
		in = out = tty;

	if (tcgetattr(fileno(in), &tty_old) == 0) {
		tty_new = tty_old;
		tty_new.c_lflag &= ~(ECHO | ISIG);

		if (tcsetattr(fileno(in), TCSAFLUSH, &tty_new) == 0)
			tty_changed = True;
	}

	if (!tty_changed)
		fputs("(WARNING: will be visible) ", out);
	fputs(prompt, out);
	fflush(out);

	read_success = fgets(password, sizeof password, in) != NULL;

	/* Print the newline that hasn't been echoed. */
	fputc('\n', out);

	if (tty_changed)
		tcsetattr(fileno(in), TCSAFLUSH, &tty_old);

	if (tty)
		fclose(tty);

	if (read_success) {
		/* Remove the trailing newline. */
		size_t password_len = strlen(password);
		if (password_len && password[password_len - 1] == '\n')
			password[password_len - 1] = '\0';

		return password;
	}

	return NULL;
}