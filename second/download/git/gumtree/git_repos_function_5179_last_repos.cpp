static void setup_branch_path(struct branch_info *branch)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_branchname(&buf, branch->name, INTERPRET_BRANCH_LOCAL);
	if (strcmp(buf.buf, branch->name))
		branch->name = xstrdup(buf.buf);
	strbuf_splice(&buf, 0, 0, "refs/heads/", 11);
	branch->path = strbuf_detach(&buf, NULL);
}