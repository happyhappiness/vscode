
	/* "--<option>=refname" or "--<option>=refname:value" */
	colon = strchrnul(arg, ':');
	entry = add_cas_entry(cas, arg, colon - arg);
	if (!*colon)
		entry->use_tracking = 1;
	else if (!colon[1])
		hashclr(entry->expect);
	else if (get_sha1(colon + 1, entry->expect))
		return error("cannot parse expected object name '%s'", colon + 1);
	return 0;
}

int parseopt_push_cas_option(const struct option *opt, const char *arg, int unset)
