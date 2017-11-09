static int get_indent(xrecord_t *rec)
{
	long i;
	int ret = 0;

	for (i = 0; i < rec->size; i++) {
		char c = rec->ptr[i];

		if (!XDL_ISSPACE(c))
			return ret;
		else if (c == ' ')
			ret += 1;
		else if (c == '\t')
			ret += 8 - ret % 8;
		/* ignore other whitespace characters */

		if (ret >= MAX_INDENT)
			return MAX_INDENT;
	}

	/* The line contains only whitespace. */
	return -1;
}