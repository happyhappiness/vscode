	strbuf_reset(sb);
	strbuf_addf(sb, "refs/tags/%s", name);

	return check_refname_format(sb->buf, 0);
}

int cmd_tag(int argc, const char **argv, const char *prefix)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf ref = STRBUF_INIT;
	unsigned char object[20], prev[20];
	const char *object_ref, *tag;
	struct create_tag_options opt;
	char *cleanup_arg = NULL;
	int create_reflog = 0;
	int annotate = 0, force = 0;
	int cmdmode = 0;
	const char *msgfile = NULL, *keyid = NULL;
	struct msg_arg msg = { 0, STRBUF_INIT };
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;
	struct ref_filter filter;
	static struct ref_sorting *sorting = NULL, **sorting_tail = &sorting;
	const char *format = NULL;
	struct option options[] = {
		OPT_CMDMODE('l', "list", &cmdmode, N_("list tag names"), 'l'),
		{ OPTION_INTEGER, 'n', NULL, &filter.lines, N_("n"),
				N_("print <n> lines of each tag message"),
				PARSE_OPT_OPTARG, NULL, 1 },
		OPT_CMDMODE('d', "delete", &cmdmode, N_("delete tags"), 'd'),
		OPT_CMDMODE('v', "verify", &cmdmode, N_("verify tags"), 'v'),

		OPT_GROUP(N_("Tag creation options")),
