	return 0;
}

static int parse_opt_sort(const struct option *opt, const char *arg, int unset)
{
	int *sort = opt->value;
	int flags = 0;

	if (*arg == '-') {
		flags |= REVERSE_SORT;
		arg++;
	}
	if (starts_with(arg, "version:")) {
		*sort = VERCMP_SORT;
		arg += 8;
	} else if (starts_with(arg, "v:")) {
		*sort = VERCMP_SORT;
		arg += 2;
	} else
		*sort = STRCMP_SORT;
	if (strcmp(arg, "refname"))
		die(_("unsupported sort specification %s"), arg);
	*sort |= flags;
	return 0;
}

int cmd_tag(int argc, const char **argv, const char *prefix)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf ref = STRBUF_INIT;
	unsigned char object[20], prev[20];
	const char *object_ref, *tag;
	struct ref_lock *lock;
	struct create_tag_options opt;
	char *cleanup_arg = NULL;
	int annotate = 0, force = 0, lines = -1;
	int cmdmode = 0, sort = 0;
	const char *msgfile = NULL, *keyid = NULL;
	struct msg_arg msg = { 0, STRBUF_INIT };
	struct commit_list *with_commit = NULL;
	struct option options[] = {
		OPT_CMDMODE('l', "list", &cmdmode, N_("list tag names"), 'l'),
		{ OPTION_INTEGER, 'n', NULL, &lines, N_("n"),
