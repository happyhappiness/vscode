static char *make_cmd(const char *prog)
{
	return xstrfmt("%s/%s", COMMAND_DIR, prog);
}