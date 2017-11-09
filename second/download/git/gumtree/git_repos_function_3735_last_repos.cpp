void prepare_submodule_repo_env(struct argv_array *out)
{
	prepare_submodule_repo_env_no_git_dir(out);
	argv_array_pushf(out, "%s=%s", GIT_DIR_ENVIRONMENT,
			 DEFAULT_GIT_DIR_ENVIRONMENT);
}