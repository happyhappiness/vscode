static int maildir_filename_cmp(const char *a, const char *b)
{
	while (*a && *b) {
		if (isdigit(*a) && isdigit(*b)) {
			long int na, nb;
			na = strtol(a, (char **)&a, 10);
			nb = strtol(b, (char **)&b, 10);
			if (na != nb)
				return na - nb;
			/* strtol advanced our pointers */
		}
		else {
			if (*a != *b)
				return (unsigned char)*a - (unsigned char)*b;
			a++;
			b++;
		}
	}
	return (unsigned char)*a - (unsigned char)*b;
}