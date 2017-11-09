static int branch_interpret_allowed(const char *refname, unsigned allowed)
{
	if (!allowed)
		return 1;

	if ((allowed & INTERPRET_BRANCH_LOCAL) &&
	    starts_with(refname, "refs/heads/"))
		return 1;
	if ((allowed & INTERPRET_BRANCH_REMOTE) &&
	    starts_with(refname, "refs/remotes/"))
		return 1;

	return 0;
}