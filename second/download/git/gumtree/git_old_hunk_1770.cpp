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
