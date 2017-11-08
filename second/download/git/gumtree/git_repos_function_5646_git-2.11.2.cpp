static const char *better_branch_name(const char *branch)
{
	static char githead_env[8 + GIT_SHA1_HEXSZ + 1];
	char *name;

	if (strlen(branch) != GIT_SHA1_HEXSZ)
		return branch;
	xsnprintf(githead_env, sizeof(githead_env), "GITHEAD_%s", branch);
	name = getenv(githead_env);
	return name ? name : branch;
}