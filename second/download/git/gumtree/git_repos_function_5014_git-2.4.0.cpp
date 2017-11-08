static char *anonymize_commit_message(const char *old)
{
	static int counter;
	return xstrfmt("subject %d\n\nbody\n", counter++);
}