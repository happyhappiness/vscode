static int verify_dotfile(const char *rest)
{
	/*
	 * The first character was '.', but that
	 * has already been discarded, we now test
	 * the rest.
	 */

	/* "." is not allowed */
	if (*rest == '\0' || is_dir_sep(*rest))
		return 0;

	switch (*rest) {
	/*
	 * ".git" followed by  NUL or slash is bad. This
	 * shares the path end test with the ".." case.
	 */
	case 'g':
	case 'G':
		if (rest[1] != 'i' && rest[1] != 'I')
			break;
		if (rest[2] != 't' && rest[2] != 'T')
			break;
		rest += 2;
	/* fallthrough */
	case '.':
		if (rest[1] == '\0' || is_dir_sep(rest[1]))
			return 0;
	}
	return 1;
}