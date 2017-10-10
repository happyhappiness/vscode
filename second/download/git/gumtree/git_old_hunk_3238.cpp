	remote->fetch_tags = 1; /* always auto-follow */
}

static int handle_config(const char *key, const char *value, void *cb)
{
	const char *name;
	const char *subkey;
	struct remote *remote;
	struct branch *branch;
	if (starts_with(key, "branch.")) {
		name = key + 7;
		subkey = strrchr(name, '.');
		if (!subkey)
			return 0;
		branch = make_branch(name, subkey - name);
		if (!strcmp(subkey, ".remote")) {
			return git_config_string(&branch->remote_name, key, value);
		} else if (!strcmp(subkey, ".pushremote")) {
			return git_config_string(&branch->pushremote_name, key, value);
		} else if (!strcmp(subkey, ".merge")) {
			if (!value)
				return config_error_nonbool(key);
			add_merge(branch, xstrdup(value));
		}
		return 0;
	}
	if (starts_with(key, "url.")) {
		struct rewrite *rewrite;
		name = key + 4;
		subkey = strrchr(name, '.');
		if (!subkey)
			return 0;
		if (!strcmp(subkey, ".insteadof")) {
			rewrite = make_rewrite(&rewrites, name, subkey - name);
			if (!value)
				return config_error_nonbool(key);
			add_instead_of(rewrite, xstrdup(value));
		} else if (!strcmp(subkey, ".pushinsteadof")) {
			rewrite = make_rewrite(&rewrites_push, name, subkey - name);
			if (!value)
				return config_error_nonbool(key);
			add_instead_of(rewrite, xstrdup(value));
		}
	}

	if (!starts_with(key,  "remote."))
		return 0;
	name = key + 7;

	/* Handle remote.* variables */
	if (!strcmp(name, "pushdefault"))
		return git_config_string(&pushremote_name, key, value);

	/* Handle remote.<name>.* variables */
	if (*name == '/') {
		warning("Config remote shorthand cannot begin with '/': %s",
			name);
		return 0;
	}
	subkey = strrchr(name, '.');
	if (!subkey)
		return 0;
	remote = make_remote(name, subkey - name);
	remote->origin = REMOTE_CONFIG;
	if (!strcmp(subkey, ".mirror"))
		remote->mirror = git_config_bool(key, value);
	else if (!strcmp(subkey, ".skipdefaultupdate"))
		remote->skip_default_update = git_config_bool(key, value);
	else if (!strcmp(subkey, ".skipfetchall"))
		remote->skip_default_update = git_config_bool(key, value);
	else if (!strcmp(subkey, ".prune"))
		remote->prune = git_config_bool(key, value);
	else if (!strcmp(subkey, ".url")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		add_url(remote, v);
	} else if (!strcmp(subkey, ".pushurl")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		add_pushurl(remote, v);
	} else if (!strcmp(subkey, ".push")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		add_push_refspec(remote, v);
	} else if (!strcmp(subkey, ".fetch")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		add_fetch_refspec(remote, v);
	} else if (!strcmp(subkey, ".receivepack")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		if (!remote->receivepack)
			remote->receivepack = v;
		else
			error("more than one receivepack given, using the first");
	} else if (!strcmp(subkey, ".uploadpack")) {
		const char *v;
		if (git_config_string(&v, key, value))
			return -1;
		if (!remote->uploadpack)
			remote->uploadpack = v;
		else
			error("more than one uploadpack given, using the first");
	} else if (!strcmp(subkey, ".tagopt")) {
		if (!strcmp(value, "--no-tags"))
			remote->fetch_tags = -1;
		else if (!strcmp(value, "--tags"))
			remote->fetch_tags = 2;
	} else if (!strcmp(subkey, ".proxy")) {
		return git_config_string((const char **)&remote->http_proxy,
					 key, value);
	} else if (!strcmp(subkey, ".vcs")) {
		return git_config_string(&remote->foreign_vcs, key, value);
	}
	return 0;
}

static void alias_all_urls(void)
