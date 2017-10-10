
	if (!head_name)
		return 0;
	return !strcmp(head_name, ref);
}

static char *refuse_unconfigured_deny_msg[] = {
	"By default, updating the current branch in a non-bare repository",
	"is denied, because it will make the index and work tree inconsistent",
	"with what you pushed, and will require 'git reset --hard' to match",
	"the work tree to HEAD.",
	"",
	"You can set 'receive.denyCurrentBranch' configuration variable to",
	"'ignore' or 'warn' in the remote repository to allow pushing into",
	"its current branch; however, this is not recommended unless you",
	"arranged to update its work tree to match what you pushed in some",
	"other way.",
	"",
	"To squelch this message and still keep the default behaviour, set",
	"'receive.denyCurrentBranch' configuration variable to 'refuse'."
};

static void refuse_unconfigured_deny(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(refuse_unconfigured_deny_msg); i++)
		rp_error("%s", refuse_unconfigured_deny_msg[i]);
}

static char *refuse_unconfigured_deny_delete_current_msg[] = {
	"By default, deleting the current branch is denied, because the next",
	"'git clone' won't result in any file checked out, causing confusion.",
	"",
	"You can set 'receive.denyDeleteCurrent' configuration variable to",
	"'warn' or 'ignore' in the remote repository to allow deleting the",
	"current branch, with or without a warning message.",
	"",
	"To squelch this message, you can set it to 'refuse'."
};

static void refuse_unconfigured_deny_delete_current(void)
{
	int i;
	for (i = 0;
	     i < ARRAY_SIZE(refuse_unconfigured_deny_delete_current_msg);
	     i++)
		rp_error("%s", refuse_unconfigured_deny_delete_current_msg[i]);
}

static int command_singleton_iterator(void *cb_data, unsigned char sha1[20]);
static int update_shallow_ref(struct command *cmd, struct shallow_info *si)
{
	static struct lock_file shallow_lock;
