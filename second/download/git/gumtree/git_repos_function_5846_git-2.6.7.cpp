char *git_terminal_prompt(const char *prompt, int echo)
{
	return getpass(prompt);
}