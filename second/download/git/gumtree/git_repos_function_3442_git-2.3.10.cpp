static struct remote *remote_get_1(const char *name, const char *pushremote_name)
{
	struct remote *ret;
	int name_given = 0;

	if (name)
		name_given = 1;
	else {
		if (pushremote_name) {
			name = pushremote_name;
			name_given = 1;
		} else {
			name = default_remote_name;
			name_given = explicit_default_remote_name;
		}
	}

	ret = make_remote(name, 0);
	if (valid_remote_nick(name)) {
		if (!valid_remote(ret))
			read_remotes_file(ret);
		if (!valid_remote(ret))
			read_branches_file(ret);
	}
	if (name_given && !valid_remote(ret))
		add_url_alias(ret, name);
	if (!valid_remote(ret))
		return NULL;
	ret->fetch = parse_fetch_refspec(ret->fetch_refspec_nr, ret->fetch_refspec);
	ret->push = parse_push_refspec(ret->push_refspec_nr, ret->push_refspec);
	return ret;
}