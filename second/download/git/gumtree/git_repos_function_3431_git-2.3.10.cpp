static void read_branches_file(struct remote *remote)
{
	char *frag;
	struct strbuf branch = STRBUF_INIT;
	int n = 1000;
	FILE *f = fopen(git_path("branches/%.*s", n, remote->name), "r");
	char *s, *p;
	int len;

	if (!f)
		return;
	s = fgets(buffer, BUF_SIZE, f);
	fclose(f);
	if (!s)
		return;
	while (isspace(*s))
		s++;
	if (!*s)
		return;
	remote->origin = REMOTE_BRANCHES;
	p = s + strlen(s);
	while (isspace(p[-1]))
		*--p = 0;
	len = p - s;
	p = xmalloc(len + 1);
	strcpy(p, s);

	/*
	 * The branches file would have URL and optionally
	 * #branch specified.  The "master" (or specified) branch is
	 * fetched and stored in the local branch of the same name.
	 */
	frag = strchr(p, '#');
	if (frag) {
		*(frag++) = '\0';
		strbuf_addf(&branch, "refs/heads/%s", frag);
	} else
		strbuf_addstr(&branch, "refs/heads/master");

	strbuf_addf(&branch, ":refs/heads/%s", remote->name);
	add_url_alias(remote, p);
	add_fetch_refspec(remote, strbuf_detach(&branch, NULL));
	/*
	 * Cogito compatible push: push current HEAD to remote #branch
	 * (master if missing)
	 */
	strbuf_init(&branch, 0);
	strbuf_addstr(&branch, "HEAD");
	if (frag)
		strbuf_addf(&branch, ":refs/heads/%s", frag);
	else
		strbuf_addstr(&branch, ":refs/heads/master");
	add_push_refspec(remote, strbuf_detach(&branch, NULL));
	remote->fetch_tags = 1; /* always auto-follow */
}