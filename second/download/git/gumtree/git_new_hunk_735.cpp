		warning("Config remote shorthand cannot begin with '/': %s",
			name);
		return 0;
	}
	remote = make_remote(name, namelen);
	remote->origin = REMOTE_CONFIG;
	if (current_config_scope() == CONFIG_SCOPE_REPO)
		remote->configured_in_repo = 1;
	if (!strcmp(subkey, "mirror"))
		remote->mirror = git_config_bool(key, value);
	else if (!strcmp(subkey, "skipdefaultupdate"))
		remote->skip_default_update = git_config_bool(key, value);
	else if (!strcmp(subkey, "skipfetchall"))
		remote->skip_default_update = git_config_bool(key, value);
