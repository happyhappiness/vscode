int validate_new_branchname(const char *name, struct strbuf *ref,
			    int force, int attr_only)
{
	if (strbuf_check_branch_ref(ref, name))
		die(_("'%s' is not a valid branch name."), name);

	if (!ref_exists(ref->buf))
		return 0;
	else if (!force && !attr_only)
		die(_("A branch named '%s' already exists."), ref->buf + strlen("refs/heads/"));

	if (!attr_only) {
		const char *head;
		struct object_id oid;

		head = resolve_ref_unsafe("HEAD", 0, oid.hash, NULL);
		if (!is_bare_repository() && head && !strcmp(head, ref->buf))
			die(_("Cannot force update the current branch."));
	}
	return 1;
}