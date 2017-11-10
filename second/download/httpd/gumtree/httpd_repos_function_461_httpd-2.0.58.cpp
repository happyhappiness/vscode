static long from_oct(int digs, char *where)
{
    register long value;

    while (apr_isspace(*where)) {	/* Skip spaces */
	where++;
	if (--digs <= 0)
	    return -1;		/* All blank field */
    }
    value = 0;
    while (digs > 0 && isodigit(*where)) {	/* Scan til nonoctal */
	value = (value << 3) | (*where++ - '0');
	--digs;
    }

    if (digs > 0 && *where && !apr_isspace(*where))
	return -1;		/* Ended on non-space/nul */

    return value;
}