	char *end;
	long nr = strtol(nr_arg, &end, 10);
	long remaining = nr;
	const char *start = refname;

	if (nr < 1 || *end != '\0')
		die(_(":strip= requires a positive integer argument"));

	while (remaining) {
		switch (*start++) {
		case '\0':
			die(_("ref '%s' does not have %ld components to :strip"),
			    refname, nr);
		case '/':
			remaining--;
			break;
		}
	}
	return start;
}

static void fill_remote_ref_details(struct used_atom *atom, const char *refname,
				    struct branch *branch, const char **s)
{
	int num_ours, num_theirs;
	if (atom->u.remote_ref == RR_SHORTEN)
		*s = shorten_unambiguous_ref(refname, warn_ambiguous_refs);
	else if (atom->u.remote_ref == RR_TRACK) {
		if (stat_tracking_info(branch, &num_ours,
				       &num_theirs, NULL))
			return;

		if (!num_ours && !num_theirs)
			*s = "";
		else if (!num_ours)
			*s = xstrfmt("[behind %d]", num_theirs);
		else if (!num_theirs)
			*s = xstrfmt("[ahead %d]", num_ours);
		else
			*s = xstrfmt("[ahead %d, behind %d]",
				     num_ours, num_theirs);
	} else if (atom->u.remote_ref == RR_TRACKSHORT) {
		if (stat_tracking_info(branch, &num_ours,
				       &num_theirs, NULL))
			return;

		if (!num_ours && !num_theirs)
			*s = "=";
		else if (!num_ours)
			*s = "<";
		else if (!num_theirs)
			*s = ">";
		else
			*s = "<>";
	} else /* RR_NORMAL */
		*s = refname;
}

/*
 * Parse the object referred by ref, and grab needed value.
 */
static void populate_value(struct ref_array_item *ref)
{
	void *buf;
