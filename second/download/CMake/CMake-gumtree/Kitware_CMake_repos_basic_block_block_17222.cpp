{
	int len;

	len = s;

	/* Octal values can't be negative, so use 0. */
	if (v < 0) {
		while (len-- > 0)
			*p++ = '0';
		return (-1);
	}

	p += s;		/* Start at the end and work backwards. */
	while (s-- > 0) {
		*--p = (char)('0' + (v & 7));
		v >>= 3;
	}

	if (v == 0)
		return (0);

	/* If it overflowed, fill field with max value. */
	while (len-- > 0)
		*p++ = '7';

	return (-1);
}