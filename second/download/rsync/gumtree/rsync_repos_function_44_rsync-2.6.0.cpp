char *get_exclude_tok(char *p)
{
	static char *s;
	static int more;
	char *t;

	if (p) {
		s=p;
		if (*p)
			more=1;
	}

	if (!more)
		return(NULL);

	/* Skip over any initial spaces */
	while (isspace(* (unsigned char *) s))
		s++;

	/* Are we at the end of the string? */
	if (*s) {
		/* remember the beginning of the token */
		t=s;

		/* Is this a '+' or '-' followed by a space (not whitespace)? */
		if ((*s=='+' || *s=='-') && *(s+1)==' ')
			s+=2;

		/* Skip to the next space or the end of the string */
		while (!isspace(* (unsigned char *) s) && *s != '\0')
			s++;
	} else {
		t=NULL;
	}

	/* Have we reached the end of the string? */
	if (*s)
		*s++='\0';
	else
		more=0;
	return(t);
}