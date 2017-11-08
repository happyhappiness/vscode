static int get_next_char(void)
{
	int c = cf->do_fgetc(cf);

	if (c == '\r') {
		/* DOS like systems */
		c = cf->do_fgetc(cf);
		if (c != '\n') {
			if (c != EOF)
				cf->do_ungetc(c, cf);
			c = '\r';
		}
	}
	if (c == '\n')
		cf->linenr++;
	if (c == EOF) {
		cf->eof = 1;
		cf->linenr++;
		c = '\n';
	}
	return c;
}