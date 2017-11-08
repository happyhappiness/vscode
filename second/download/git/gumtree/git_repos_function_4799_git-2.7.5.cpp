static void NORETURN die_user_resolve(const struct am_state *state)
{
	if (state->resolvemsg) {
		printf_ln("%s", state->resolvemsg);
	} else {
		const char *cmdline = state->interactive ? "git am -i" : "git am";

		printf_ln(_("When you have resolved this problem, run \"%s --continue\"."), cmdline);
		printf_ln(_("If you prefer to skip this patch, run \"%s --skip\" instead."), cmdline);
		printf_ln(_("To restore the original branch and stop patching, run \"%s --abort\"."), cmdline);
	}

	exit(128);
}