static void write_arg(int fd, char *arg)
{
	char *x, *s;

	if (*arg == '-' && (x = strchr(arg, '=')) != NULL) {
		write(fd, arg, x - arg + 1);
		arg += x - arg + 1;
	}

	if (strpbrk(arg, " \"'&;|[]()$#!*?^\\") != NULL) {
		write(fd, "'", 1);
		for (s = arg; (x = strchr(s, '\'')) != NULL; s = x + 1) {
			write(fd, s, x - s + 1);
			write(fd, "'", 1);
		}
		write(fd, s, strlen(s));
		write(fd, "'", 1);
		return;
	}

	write(fd, arg, strlen(arg));
}