static char *find_branch_name(struct rev_info *rev)
{
	int i, positive = -1;
	unsigned char branch_sha1[20];
	const unsigned char *tip_sha1;
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
	tip_sha1 = rev->cmdline.rev[positive].item->sha1;
	if (dwim_ref(ref, strlen(ref), branch_sha1, &full_ref) &&
	    skip_prefix(full_ref, "refs/heads/", &v) &&
	    !hashcmp(tip_sha1, branch_sha1))
		branch = xstrdup(v);
	free(full_ref);
	return branch;
}