static int skip_imap_list_l(char **sp, int level)
{
	char *s = *sp;

	for (;;) {
		while (isspace((unsigned char)*s))
			s++;
		if (level && *s == ')') {
			s++;
			break;
		}
		if (*s == '(') {
			/* sublist */
			s++;
			if (skip_imap_list_l(&s, level + 1))
				goto bail;
		} else if (*s == '"') {
			/* quoted string */
			s++;
			for (; *s != '"'; s++)
				if (!*s)
					goto bail;
			s++;
		} else {
			/* atom */
			for (; *s && !isspace((unsigned char)*s); s++)
				if (level && *s == ')')
					break;
		}

		if (!level)
			break;
		if (!*s)
			goto bail;
	}
	*sp = s;
	return 0;

bail:
	return -1;
}