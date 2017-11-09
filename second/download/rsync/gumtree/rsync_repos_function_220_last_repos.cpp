static int write_arg(int fd, char *arg)
{
	char *x, *s;
	int len, ret = 0;

	if (*arg == '-' && (x = strchr(arg, '=')) != NULL) {
		if (write(fd, arg, x - arg + 1) != x - arg + 1)
			ret = -1;
		arg += x - arg + 1;
	}

	if (strpbrk(arg, " \"'&;|[]()$#!*?^\\") != NULL) {
		if (write(fd, "'", 1) != 1)
			ret = -1;
		for (s = arg; (x = strchr(s, '\'')) != NULL; s = x + 1) {
			if (write(fd, s, x - s + 1) != x - s + 1
			 || write(fd, "'", 1) != 1)
				ret = -1;
		}
		len = strlen(s);
		if (write(fd, s, len) != len
		 || write(fd, "'", 1) != 1)
			ret = -1;
		return ret;
	}

	len = strlen(arg);
	if (write(fd, arg, len) != len)
		ret = -1;

	return ret;
}