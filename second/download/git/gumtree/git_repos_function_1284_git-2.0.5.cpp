int parse_hunk_header(char *line, int len,
		      int *ob, int *on,
		      int *nb, int *nn)
{
	char *cp;
	cp = line + 4;
	if (parse_num(&cp, ob)) {
	bad_line:
		return error("malformed diff output: %s", line);
	}
	if (*cp == ',') {
		cp++;
		if (parse_num(&cp, on))
			goto bad_line;
	}
	else
		*on = 1;
	if (*cp++ != ' ' || *cp++ != '+')
		goto bad_line;
	if (parse_num(&cp, nb))
		goto bad_line;
	if (*cp == ',') {
		cp++;
		if (parse_num(&cp, nn))
			goto bad_line;
	}
	else
		*nn = 1;
	return -!!memcmp(cp, " @@", 3);
}