int parse_push_cas_option(struct push_cas_option *cas, const char *arg, int unset)
{
	const char *colon;
	struct push_cas *entry;

	if (unset) {
		/* "--no-<option>" */
		clear_cas_option(cas);
		return 0;
	}

	if (!arg) {
		/* just "--<option>" */
		cas->use_tracking_for_rest = 1;
		return 0;
	}

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