int git_gpg_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "user.signingkey")) {
		set_signing_key(value);
	}
	if (!strcmp(var, "gpg.program")) {
		if (!value)
			return config_error_nonbool(var);
		gpg_program = xstrdup(value);
	}
	return 0;
}