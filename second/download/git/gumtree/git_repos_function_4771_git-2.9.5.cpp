static int option_parse_directory(const struct option *opt,
				  const char *arg, int unset)
{
	strbuf_reset(&root);
	strbuf_addstr(&root, arg);
	strbuf_complete(&root, '/');
	return 0;
}