int cmd_update_ref(int argc, const char **argv, const char *prefix)
{
	const char *refname, *oldval;
	unsigned char sha1[20], oldsha1[20];
	int delete = 0, no_deref = 0, read_stdin = 0, end_null = 0;
	unsigned int flags = 0;
	int create_reflog = 0;
	struct option options[] = {
		OPT_STRING( 'm', NULL, &msg, N_("reason"), N_("reason of the update")),
		OPT_BOOL('d', NULL, &delete, N_("delete the reference")),
		OPT_BOOL( 0 , "no-deref", &no_deref,
					N_("update <refname> not the one it points to")),
		OPT_BOOL('z', NULL, &end_null, N_("stdin has NUL-terminated arguments")),
		OPT_BOOL( 0 , "stdin", &read_stdin, N_("read updates from stdin")),
		OPT_BOOL( 0 , "create-reflog", &create_reflog, N_("create a reflog")),
		OPT_END(),
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, options, git_update_ref_usage,
			     0);
	if (msg && !*msg)
		die("Refusing to perform update with empty message.");

	create_reflog_flag = create_reflog ? REF_FORCE_CREATE_REFLOG : 0;

	if (read_stdin) {
		struct strbuf err = STRBUF_INIT;
		struct ref_transaction *transaction;

		transaction = ref_transaction_begin(&err);
		if (!transaction)
