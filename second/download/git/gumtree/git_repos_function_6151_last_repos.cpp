static void add_branch(const char *key, const char *branchname,
		       const char *remotename, int mirror, struct strbuf *tmp)
{
	strbuf_reset(tmp);
	strbuf_addch(tmp, '+');
	if (mirror)
		strbuf_addf(tmp, "refs/%s:refs/%s",
				branchname, branchname);
	else
		strbuf_addf(tmp, "refs/heads/%s:refs/remotes/%s/%s",
				branchname, remotename, branchname);
	git_config_set_multivar(key, tmp->buf, "^$", 0);
}