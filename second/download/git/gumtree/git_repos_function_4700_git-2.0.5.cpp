static void update_head(const struct ref *our, const struct ref *remote,
			const char *msg)
{
	if (our && starts_with(our->name, "refs/heads/")) {
		/* Local default branch link */
		create_symref("HEAD", our->name, NULL);
		if (!option_bare) {
			const char *head = skip_prefix(our->name, "refs/heads/");
			update_ref(msg, "HEAD", our->old_sha1, NULL, 0, DIE_ON_ERR);
			install_branch_config(0, head, option_origin, our->name);
		}
	} else if (our) {
		struct commit *c = lookup_commit_reference(our->old_sha1);
		/* --branch specifies a non-branch (i.e. tags), detach HEAD */
		update_ref(msg, "HEAD", c->object.sha1,
			   NULL, REF_NODEREF, DIE_ON_ERR);
	} else if (remote) {
		/*
		 * We know remote HEAD points to a non-branch, or
		 * HEAD points to a branch but we don't know which one.
		 * Detach HEAD in all these cases.
		 */
		update_ref(msg, "HEAD", remote->old_sha1,
			   NULL, REF_NODEREF, DIE_ON_ERR);
	}
}