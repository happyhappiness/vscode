static int parse_next_sha1(struct strbuf *input, const char **next,
			   unsigned char *sha1,
			   const char *command, const char *refname,
			   int flags)
{
	struct strbuf arg = STRBUF_INIT;
	int ret = 0;

	if (*next == input->buf + input->len)
		goto eof;

	if (line_termination) {
		/* Without -z, consume SP and use next argument */
		if (!**next || **next == line_termination)
			return 1;
		if (**next != ' ')
			die("%s %s: expected SP but got: %s",
			    command, refname, *next);
		(*next)++;
		*next = parse_arg(*next, &arg);
		if (arg.len) {
			if (get_sha1(arg.buf, sha1))
				goto invalid;
		} else {
			/* Without -z, an empty value means all zeros: */
			hashclr(sha1);
		}
	} else {
		/* With -z, read the next NUL-terminated line */
		if (**next)
			die("%s %s: expected NUL but got: %s",
			    command, refname, *next);
		(*next)++;
		if (*next == input->buf + input->len)
			goto eof;
		strbuf_addstr(&arg, *next);
		*next += arg.len;

		if (arg.len) {
			if (get_sha1(arg.buf, sha1))
				goto invalid;
		} else if (flags & PARSE_SHA1_ALLOW_EMPTY) {
			/* With -z, treat an empty value as all zeros: */
			warning("%s %s: missing <newvalue>, treating as zero",
				command, refname);
			hashclr(sha1);
		} else {
			/*
			 * With -z, an empty non-required value means
			 * unspecified:
			 */
			ret = 1;
		}
	}

	strbuf_release(&arg);

	return ret;

 invalid:
	die(flags & PARSE_SHA1_OLD ?
	    "%s %s: invalid <oldvalue>: %s" :
	    "%s %s: invalid <newvalue>: %s",
	    command, refname, arg.buf);

 eof:
	die(flags & PARSE_SHA1_OLD ?
	    "%s %s: unexpected end of input when reading <oldvalue>" :
	    "%s %s: unexpected end of input when reading <newvalue>",
	    command, refname);
}