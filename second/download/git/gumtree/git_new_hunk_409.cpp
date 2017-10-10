
	if (!head_name)
		return 0;
	return !strcmp(head_name, ref);
}

static char *refuse_unconfigured_deny_msg =
	N_("By default, updating the current branch in a non-bare repository\n"
	   "is denied, because it will make the index and work tree inconsistent\n"
	   "with what you pushed, and will require 'git reset --hard' to match\n"
	   "the work tree to HEAD.\n"
	   "\n"
	   "You can set 'receive.denyCurrentBranch' configuration variable to\n"
	   "'ignore' or 'warn' in the remote repository to allow pushing into\n"
	   "its current branch; however, this is not recommended unless you\n"
	   "arranged to update its work tree to match what you pushed in some\n"
	   "other way.\n"
	   "\n"
	   "To squelch this message and still keep the default behaviour, set\n"
	   "'receive.denyCurrentBranch' configuration variable to 'refuse'.");

static void refuse_unconfigured_deny(void)
{
	rp_error("%s", _(refuse_unconfigured_deny_msg));
}

static char *refuse_unconfigured_deny_delete_current_msg =
	N_("By default, deleting the current branch is denied, because the next\n"
	   "'git clone' won't result in any file checked out, causing confusion.\n"
	   "\n"
	   "You can set 'receive.denyDeleteCurrent' configuration variable to\n"
	   "'warn' or 'ignore' in the remote repository to allow deleting the\n"
	   "current branch, with or without a warning message.\n"
	   "\n"
	   "To squelch this message, you can set it to 'refuse'.");

static void refuse_unconfigured_deny_delete_current(void)
{
	rp_error("%s", _(refuse_unconfigured_deny_delete_current_msg));
}

static int command_singleton_iterator(void *cb_data, unsigned char sha1[20]);
static int update_shallow_ref(struct command *cmd, struct shallow_info *si)
{
	static struct lock_file shallow_lock;
