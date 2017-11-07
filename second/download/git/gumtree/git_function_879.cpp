static void fill_remote_ref_details(struct used_atom *atom, const char *refname,
				    struct branch *branch, const char **s)
{
	int num_ours, num_theirs;
	if (atom->u.remote_ref.option == RR_REF)
		*s = show_ref(&atom->u.remote_ref.refname, refname);
	else if (atom->u.remote_ref.option == RR_TRACK) {
		if (stat_tracking_info(branch, &num_ours,
				       &num_theirs, NULL)) {
			*s = xstrdup(msgs.gone);
		} else if (!num_ours && !num_theirs)
			*s = "";
		else if (!num_ours)
			*s = xstrfmt(msgs.behind, num_theirs);
		else if (!num_theirs)
			*s = xstrfmt(msgs.ahead, num_ours);
		else
			*s = xstrfmt(msgs.ahead_behind,
				     num_ours, num_theirs);
		if (!atom->u.remote_ref.nobracket && *s[0]) {
			const char *to_free = *s;
			*s = xstrfmt("[%s]", *s);
			free((void *)to_free);
		}
	} else if (atom->u.remote_ref.option == RR_TRACKSHORT) {
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
	} else
		die("BUG: unhandled RR_* enum");
}