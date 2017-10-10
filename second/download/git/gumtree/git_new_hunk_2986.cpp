	strbuf_release(&err);
	if (t)
		ref_transaction_free(t);
	return 0;
}

char *shorten_unambiguous_ref(const char *refname, int strict)
{
	int i;
	static char **scanf_fmts;
	static int nr_rules;
	char *short_name;
