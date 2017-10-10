		return _(implicit_ident_advice_config);
	else
		return _(implicit_ident_advice_noconfig);

}

static void print_summary(const char *prefix, const unsigned char *sha1,
			  int initial_commit)
{
	struct rev_info rev;
	struct commit *commit;
	struct strbuf format = STRBUF_INIT;
	unsigned char junk_sha1[20];
	const char *head;
	struct pretty_print_context pctx = {0};
	struct strbuf author_ident = STRBUF_INIT;
	struct strbuf committer_ident = STRBUF_INIT;

	commit = lookup_commit(sha1);
	if (!commit)
		die(_("couldn't look up newly created commit"));
	if (parse_commit(commit))
		die(_("could not parse newly created commit"));

	strbuf_addstr(&format, "format:%h] %s");
