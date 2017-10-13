char *git_prompt(const char *prompt, int flags)
{
	char *r = NULL;

	if (flags & PROMPT_ASKPASS) {
		const char *askpass;

		askpass = getenv("GIT_ASKPASS");
		if (!askpass)
			askpass = askpass_program;
		if (!askpass)
			askpass = getenv("SSH_ASKPASS");
		if (askpass && *askpass)
			r = do_askpass(askpass, prompt);
	}

	if (!r)
		r = git_terminal_prompt(prompt, flags & PROMPT_ECHO);
	if (!r) {
		/* prompts already contain ": " at the end */
		die("could not read %s%s", prompt, strerror(errno));
	}
	return r;
}