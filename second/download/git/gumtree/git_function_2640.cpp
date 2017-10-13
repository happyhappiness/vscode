static const char **parse_argv(const char *arg, const char *service)
{
	int arguments = 0;
	int i;
	const char **ret;
	char *temparray[MAXARGUMENTS + 1];

	while (*arg) {
		char *expanded;
		if (arguments == MAXARGUMENTS)
			die("remote-ext command has too many arguments");
		expanded = strip_escapes(arg, service, &arg);
		if (expanded)
			temparray[arguments++] = expanded;
	}

	ret = xmalloc((arguments + 1) * sizeof(char *));
	for (i = 0; i < arguments; i++)
		ret[i] = temparray[i];
	ret[arguments] = NULL;
	return ret;
}