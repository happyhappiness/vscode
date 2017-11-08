static const char *find_next(const char *cp)
{
	while (*cp) {
		if (*cp == '%') {
			/*
			 * %( is the start of an atom;
			 * %% is a quoted per-cent.
			 */
			if (cp[1] == '(')
				return cp;
			else if (cp[1] == '%')
				cp++; /* skip over two % */
			/* otherwise this is a singleton, literal % */
		}
		cp++;
	}
	return NULL;
}