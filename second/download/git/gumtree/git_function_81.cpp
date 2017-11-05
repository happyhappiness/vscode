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