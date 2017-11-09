int git_ident_config(const char *var, const char *value, void *data)
{
	if (!strcmp(var, "user.useconfigonly")) {
		ident_use_config_only = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "user.name")) {
		if (!value)
			return config_error_nonbool(var);
		strbuf_reset(&git_default_name);
		strbuf_addstr(&git_default_name, value);
		committer_ident_explicitly_given |= IDENT_NAME_GIVEN;
		author_ident_explicitly_given |= IDENT_NAME_GIVEN;
		ident_config_given |= IDENT_NAME_GIVEN;
		return 0;
	}

	if (!strcmp(var, "user.email")) {
		if (!value)
			return config_error_nonbool(var);
		strbuf_reset(&git_default_email);
		strbuf_addstr(&git_default_email, value);
		committer_ident_explicitly_given |= IDENT_MAIL_GIVEN;
		author_ident_explicitly_given |= IDENT_MAIL_GIVEN;
		ident_config_given |= IDENT_MAIL_GIVEN;
		return 0;
	}

	return 0;
}