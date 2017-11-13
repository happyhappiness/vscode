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