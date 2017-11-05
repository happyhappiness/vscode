int is_transport_allowed(const char *type, int from_user)
{
	const struct string_list *whitelist = protocol_whitelist();
	if (whitelist)
		return string_list_has_string(whitelist, type);

	switch (get_protocol_config(type)) {
	case PROTOCOL_ALLOW_ALWAYS:
		return 1;
	case PROTOCOL_ALLOW_NEVER:
		return 0;
	case PROTOCOL_ALLOW_USER_ONLY:
		if (from_user < 0)
			from_user = git_env_bool("GIT_PROTOCOL_FROM_USER", 1);
		return from_user;
	}

	die("BUG: invalid protocol_allow_config type");
}