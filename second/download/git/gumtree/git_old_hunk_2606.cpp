		die_errno("close failed on standard output");
	return 0;
}

static struct cmd_struct commands[] = {
	{ "add", cmd_add, RUN_SETUP | NEED_WORK_TREE },
	{ "annotate", cmd_annotate, RUN_SETUP },
	{ "apply", cmd_apply, RUN_SETUP_GENTLY },
	{ "archive", cmd_archive },
	{ "bisect--helper", cmd_bisect__helper, RUN_SETUP },
	{ "blame", cmd_blame, RUN_SETUP },
	{ "branch", cmd_branch, RUN_SETUP },
