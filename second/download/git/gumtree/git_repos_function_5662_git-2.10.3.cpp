static void add_branches(struct remote *remote, const char **branches,
			 const char *key)
{
	const char *remotename = remote->name;
	int mirror = remote->mirror;
	struct strbuf refspec = STRBUF_INIT;

	for (; *branches; branches++)
		add_branch(key, *branches, remotename, mirror, &refspec);

	strbuf_release(&refspec);
}