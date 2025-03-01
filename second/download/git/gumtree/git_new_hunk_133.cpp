	N_("git update-ref [options] -d <refname> [<oldval>]"),
	N_("git update-ref [options]    <refname> <newval> [<oldval>]"),
	N_("git update-ref [options] --stdin [-z]"),
	NULL
};

static struct ref_transaction *transaction;

static char line_termination = '\n';
static int update_flags;
static struct strbuf err = STRBUF_INIT;

/*
 * Parse one whitespace- or NUL-terminated, possibly C-quoted argument
 * and append the result to arg.  Return a pointer to the terminator.
 * Die if there is an error in how the argument is C-quoted.  This
 * function is only used if not -z.
 */
static const char *parse_arg(const char *next, struct strbuf *arg)
{
	if (*next == '"') {
		const char *orig = next;

		if (unquote_c_style(arg, next, &next))
			die("badly quoted argument: %s", orig);
		if (*next && !isspace(*next))
			die("unexpected character after quoted argument: %s", orig);
	} else {
		while (*next && !isspace(*next))
			strbuf_addch(arg, *next++);
	}

	return next;
}

/*
 * Parse the reference name immediately after "command SP".  If not
 * -z, then handle C-quoting.  Return a pointer to a newly allocated
 * string containing the name of the reference, or NULL if there was
 * an error.  Update *next to point at the character that terminates
 * the argument.  Die if C-quoting is malformed or the reference name
 * is invalid.
 */
static char *parse_refname(struct strbuf *input, const char **next)
{
	struct strbuf ref = STRBUF_INIT;

	if (line_termination) {
		/* Without -z, use the next argument */
		*next = parse_arg(*next, &ref);
	} else {
		/* With -z, use everything up to the next NUL */
		strbuf_addstr(&ref, *next);
		*next += ref.len;
	}

	if (!ref.len) {
		strbuf_release(&ref);
		return NULL;
	}

	if (check_refname_format(ref.buf, REFNAME_ALLOW_ONELEVEL))
		die("invalid ref format: %s", ref.buf);

	return strbuf_detach(&ref, NULL);
}

/*
 * The value being parsed is <oldvalue> (as opposed to <newvalue>; the
 * difference affects which error messages are generated):
 */
#define PARSE_SHA1_OLD 0x01

/*
 * For backwards compatibility, accept an empty string for update's
 * <newvalue> in binary mode to be equivalent to specifying zeros.
 */
#define PARSE_SHA1_ALLOW_EMPTY 0x02

/*
 * Parse an argument separator followed by the next argument, if any.
 * If there is an argument, convert it to a SHA-1, write it to sha1,
 * set *next to point at the character terminating the argument, and
 * return 0.  If there is no argument at all (not even the empty
 * string), return 1 and leave *next unchanged.  If the value is
 * provided but cannot be converted to a SHA-1, die.  flags can
 * include PARSE_SHA1_OLD and/or PARSE_SHA1_ALLOW_EMPTY.
 */
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


/*
 * The following five parse_cmd_*() functions parse the corresponding
 * command.  In each case, next points at the character following the
 * command name and the following space.  They each return a pointer
 * to the character terminating the command, and die with an
 * explanatory message if there are any parsing problems.  All of
 * these functions handle either text or binary format input,
 * depending on how line_termination is set.
 */

static const char *parse_cmd_update(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
	if (!refname)
		die("update: missing <ref>");

	if (parse_next_sha1(input, &next, new_sha1, "update", refname,
			    PARSE_SHA1_ALLOW_EMPTY))
		die("update %s: missing <newvalue>", refname);

	have_old = !parse_next_sha1(input, &next, old_sha1, "update", refname,
				    PARSE_SHA1_OLD);

	if (*next != line_termination)
		die("update %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_create(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];

	refname = parse_refname(input, &next);
	if (!refname)
		die("create: missing <ref>");

	if (parse_next_sha1(input, &next, new_sha1, "create", refname, 0))
		die("create %s: missing <newvalue>", refname);

	if (is_null_sha1(new_sha1))
		die("create %s: zero <newvalue>", refname);

	if (*next != line_termination)
		die("create %s: extra input: %s", refname, next);

	ref_transaction_create(transaction, refname, new_sha1, update_flags);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_delete(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
	if (!refname)
		die("delete: missing <ref>");

	if (parse_next_sha1(input, &next, old_sha1, "delete", refname,
			    PARSE_SHA1_OLD)) {
		have_old = 0;
	} else {
		if (is_null_sha1(old_sha1))
			die("delete %s: zero <oldvalue>", refname);
		have_old = 1;
	}

	if (*next != line_termination)
		die("delete %s: extra input: %s", refname, next);

	ref_transaction_delete(transaction, refname, old_sha1,
			       update_flags, have_old);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_verify(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
	if (!refname)
		die("verify: missing <ref>");

	if (parse_next_sha1(input, &next, old_sha1, "verify", refname,
			    PARSE_SHA1_OLD)) {
		hashclr(new_sha1);
		have_old = 0;
	} else {
		hashcpy(new_sha1, old_sha1);
		have_old = 1;
	}

	if (*next != line_termination)
		die("verify %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_option(struct strbuf *input, const char *next)
{
	if (!strncmp(next, "no-deref", 8) && next[8] == line_termination)
		update_flags |= REF_NODEREF;
	else
		die("option unknown: %s", next);
	return next + 8;
}

static void update_refs_stdin(void)
{
	struct strbuf input = STRBUF_INIT;
	const char *next;

	if (strbuf_read(&input, 0, 1000) < 0)
		die_errno("could not read from stdin");
	next = input.buf;
	/* Read each line dispatch its command */
	while (next < input.buf + input.len) {
		if (*next == line_termination)
			die("empty command in input");
		else if (isspace(*next))
			die("whitespace before command: %s", next);
		else if (starts_with(next, "update "))
			next = parse_cmd_update(&input, next + 7);
		else if (starts_with(next, "create "))
			next = parse_cmd_create(&input, next + 7);
		else if (starts_with(next, "delete "))
			next = parse_cmd_delete(&input, next + 7);
		else if (starts_with(next, "verify "))
			next = parse_cmd_verify(&input, next + 7);
		else if (starts_with(next, "option "))
			next = parse_cmd_option(&input, next + 7);
		else
			die("unknown command: %s", next);

		next++;
	}

	strbuf_release(&input);
}

int cmd_update_ref(int argc, const char **argv, const char *prefix)
{
	const char *refname, *oldval, *msg = NULL;
	unsigned char sha1[20], oldsha1[20];
