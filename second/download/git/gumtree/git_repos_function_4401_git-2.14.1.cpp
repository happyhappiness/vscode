static void read_branches_file(struct remote *remote)
{
	char *frag;
	struct strbuf buf = STRBUF_INIT;
	FILE *f = fopen_or_warn(git_path("branches/%s", remote->name), "r");

	if (!f)
		return;

	strbuf_getline_lf(&buf, f);
	fclose(f);
	strbuf_trim(&buf);
	if (!buf.len) {
		strbuf_release(&buf);
		return;
	}

	remote->configured_in_repo = 1;
	remote->origin = REMOTE_BRANCHES;

	/*
	 * The branches file would have URL and optionally
	 * #branch specified.  The "master" (or specified) branch is
	 * fetched and stored in the local branch matching the
	 * remote name.
	 */
	frag = strchr(buf.buf, '#');
	if (frag)
		*(frag++) = '\0';
	else
		frag = "master";

	add_url_alias(remote, strbuf_detach(&buf, NULL));
	add_fetch_refspec(remote, xstrfmt("refs/heads/%s:refs/heads/%s",
					  frag, remote->name));

	/*
	 * Cogito compatible push: push current HEAD to remote #branch
	 * (master if missing)
	 */
	add_push_refspec(remote, xstrfmt("HEAD:refs/heads/%s", frag));
	remote->fetch_tags = 1; /* always auto-follow */
}