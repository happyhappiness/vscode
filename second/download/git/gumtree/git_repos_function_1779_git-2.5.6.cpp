const char *setup_git_directory_gently(int *nongit_ok)
{
	const char *prefix;

	prefix = setup_git_directory_gently_1(nongit_ok);
	if (prefix)
		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
	else
		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);

	if (startup_info) {
		startup_info->have_repository = !nongit_ok || !*nongit_ok;
		startup_info->prefix = prefix;
	}
	return prefix;
}