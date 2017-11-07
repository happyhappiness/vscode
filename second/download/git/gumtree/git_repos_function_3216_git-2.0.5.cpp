static struct branch *make_branch(const char *name, int len)
{
	struct branch *ret;
	int i;
	char *refname;

	for (i = 0; i < branches_nr; i++) {
		if (len ? (!strncmp(name, branches[i]->name, len) &&
			   !branches[i]->name[len]) :
		    !strcmp(name, branches[i]->name))
			return branches[i];
	}

	ALLOC_GROW(branches, branches_nr + 1, branches_alloc);
	ret = xcalloc(1, sizeof(struct branch));
	branches[branches_nr++] = ret;
	if (len)
		ret->name = xstrndup(name, len);
	else
		ret->name = xstrdup(name);
	refname = xmalloc(strlen(name) + strlen("refs/heads/") + 1);
	strcpy(refname, "refs/heads/");
	strcpy(refname + strlen("refs/heads/"), ret->name);
	ret->refname = refname;

	return ret;
}