char *git_getpass(const char *prompt)
{
	return git_prompt(prompt, PROMPT_ASKPASS);
}