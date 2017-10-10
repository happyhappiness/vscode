{
	while (*src)
		*dst++ = *src++;
	return dst;
}

static const char *lstrip_ref_components(const char *refname, int len)
{
	long remaining = len;
	const char *start = refname;

	if (len < 0) {
		int i;
		const char *p = refname;

		/* Find total no of '/' separated path-components */
		for (i = 0; p[i]; p[i] == '/' ? i++ : *p++)
			;
		/*
		 * The number of components we need to strip is now
		 * the total minus the components to be left (Plus one
		 * because we count the number of '/', but the number
		 * of components is one more than the no of '/').
		 */
		remaining = i + len + 1;
	}

	while (remaining > 0) {
		switch (*start++) {
		case '\0':
			return "";
		case '/':
			remaining--;
			break;
		}
	}

	return start;
}

static const char *rstrip_ref_components(const char *refname, int len)
{
	long remaining = len;
	char *start = xstrdup(refname);

	if (len < 0) {
		int i;
		const char *p = refname;

		/* Find total no of '/' separated path-components */
		for (i = 0; p[i]; p[i] == '/' ? i++ : *p++)
			;
		/*
		 * The number of components we need to strip is now
		 * the total minus the components to be left (Plus one
		 * because we count the number of '/', but the number
		 * of components is one more than the no of '/').
		 */
		remaining = i + len + 1;
	}

	while (remaining-- > 0) {
		char *p = strrchr(start, '/');
		if (p == NULL)
			return "";
		else
			p[0] = '\0';
	}
	return start;
}

static const char *show_ref(struct refname_atom *atom, const char *refname)
{
	if (atom->option == R_SHORT)
		return shorten_unambiguous_ref(refname, warn_ambiguous_refs);
	else if (atom->option == R_LSTRIP)
		return lstrip_ref_components(refname, atom->lstrip);
	else if (atom->option == R_RSTRIP)
		return rstrip_ref_components(refname, atom->rstrip);
	else
		return refname;
}

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

char *get_head_description(void)
{
	struct strbuf desc = STRBUF_INIT;
	struct wt_status_state state;
	memset(&state, 0, sizeof(state));
	wt_status_get_state(&state, 1);
	if (state.rebase_in_progress ||
	    state.rebase_interactive_in_progress)
		strbuf_addf(&desc, _("(no branch, rebasing %s)"),
			    state.branch);
	else if (state.bisect_in_progress)
		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
			    state.branch);
	else if (state.detached_from) {
		if (state.detached_at)
			/* TRANSLATORS: make sure this matches
			   "HEAD detached at " in wt-status.c */
			strbuf_addf(&desc, _("(HEAD detached at %s)"),
				state.detached_from);
		else
			/* TRANSLATORS: make sure this matches
			   "HEAD detached from " in wt-status.c */
			strbuf_addf(&desc, _("(HEAD detached from %s)"),
				state.detached_from);
	}
	else
		strbuf_addstr(&desc, _("(no branch)"));
	free(state.branch);
	free(state.onto);
	free(state.detached_from);
	return strbuf_detach(&desc, NULL);
}

static const char *get_symref(struct used_atom *atom, struct ref_array_item *ref)
{
	if (!ref->symref)
		return "";
	else
		return show_ref(&atom->u.refname, ref->symref);
}

static const char *get_refname(struct used_atom *atom, struct ref_array_item *ref)
{
	if (ref->kind & FILTER_REFS_DETACHED_HEAD)
		return get_head_description();
	return show_ref(&atom->u.refname, ref->refname);
}

/*
 * Parse the object referred by ref, and grab needed value.
 */
static void populate_value(struct ref_array_item *ref)
