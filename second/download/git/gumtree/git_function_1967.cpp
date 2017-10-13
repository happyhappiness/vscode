static const char *get_upstream_branch(const char *branch_buf, int len)
{
	char *branch = xstrndup(branch_buf, len);
	struct branch *upstream = branch_get(*branch ? branch : NULL);

	/*
	 * Upstream can be NULL only if branch refers to HEAD and HEAD
	 * points to something different than a branch.
	 */
	if (!upstream)
		die(_("HEAD does not point to a branch"));
	if (!upstream->merge || !upstream->merge[0]->dst) {
		if (!ref_exists(upstream->refname))
			die(_("No such branch: '%s'"), branch);
		if (!upstream->merge) {
			die(_("No upstream configured for branch '%s'"),
				upstream->name);
		}
		die(
			_("Upstream branch '%s' not stored as a remote-tracking branch"),
			upstream->merge[0]->src);
	}
	free(branch);

	return upstream->merge[0]->dst;
}