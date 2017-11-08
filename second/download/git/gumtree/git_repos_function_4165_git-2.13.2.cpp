void strbuf_branchname(struct strbuf *sb, const char *name, unsigned allowed)
{
	int len = strlen(name);
	int used = interpret_branch_name(name, len, sb, allowed);

	if (used < 0)
		used = 0;
	strbuf_add(sb, name + used, len - used);
}