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