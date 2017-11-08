static char *find_branch_name(struct rev_info *rev)
{
	int i, positive = -1;
	struct object_id branch_oid;
	const struct object_id *tip_oid;
	const char *ref, *v;
	char *full_ref, *branch = NULL;

	for (i = 0; i < rev->cmdline.nr; i++) {
		if (rev->cmdline.rev[i].flags & UNINTERESTING)
			continue;
		if (positive < 0)
			positive = i;
		else
			return NULL;
	}
	if (positive < 0)
		return NULL;
	ref = rev->cmdline.rev[positive].name;
	tip_oid = &rev->cmdline.rev[positive].item->oid;
	if (dwim_ref(ref, strlen(ref), branch_oid.hash, &full_ref) &&
	    skip_prefix(full_ref, "refs/heads/", &v) &&
	    !oidcmp(tip_oid, &branch_oid))
		branch = xstrdup(v);
	free(full_ref);
	return branch;
}