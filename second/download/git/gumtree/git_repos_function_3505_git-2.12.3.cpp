void prepare_submodule_repo_env(struct argv_array *out)
{
	const char * const *var;

	for (var = local_repo_env; *var; var++) {
		if (strcmp(*var, CONFIG_DATA_ENVIRONMENT))
			argv_array_push(out, *var);
	}
	argv_array_pushf(out, "%s=%s", GIT_DIR_ENVIRONMENT,
			 DEFAULT_GIT_DIR_ENVIRONMENT);
}