static struct remote *make_remote(const char *name, int len)
{
	struct remote *ret;
	int i;

	for (i = 0; i < remotes_nr; i++) {
		if (len ? (!strncmp(name, remotes[i]->name, len) &&
			   !remotes[i]->name[len]) :
		    !strcmp(name, remotes[i]->name))
			return remotes[i];
	}

	ret = xcalloc(1, sizeof(struct remote));
	ret->prune = -1;  /* unspecified */
	ALLOC_GROW(remotes, remotes_nr + 1, remotes_alloc);
	remotes[remotes_nr++] = ret;
	if (len)
		ret->name = xstrndup(name, len);
	else
		ret->name = xstrdup(name);
	return ret;
}