static char *make_cmd(const char *prog)
{
	char *prefix = xmalloc((strlen(prog) + strlen(COMMAND_DIR) + 2));
	strcpy(prefix, COMMAND_DIR);
	strcat(prefix, "/");
	strcat(prefix, prog);
	return prefix;
}