	if (!empty_commit)
		return 0;
	else
		return 1;
}

enum todo_command {
	TODO_PICK = 0,
	TODO_REVERT
};

static const char *todo_command_strings[] = {
	"pick",
	"revert"
};

static const char *command_to_string(const enum todo_command command)
{
	if ((size_t)command < ARRAY_SIZE(todo_command_strings))
		return todo_command_strings[command];
	die("Unknown command: %d", command);
}


static int do_pick_commit(enum todo_command command, struct commit *commit,
		struct replay_opts *opts)
{
	unsigned char head[20];
	struct commit *base, *next, *parent;
	const char *base_label, *next_label;
	struct commit_message msg = { NULL, NULL, NULL, NULL };
	struct strbuf msgbuf = STRBUF_INIT;
	int res, unborn = 0, allow;

	if (opts->no_commit) {
		/*
		 * We do not intend to commit immediately.  We just want to
		 * merge the differences in, so let's compute the tree
		 * that represents the "current" state for merge-recursive
