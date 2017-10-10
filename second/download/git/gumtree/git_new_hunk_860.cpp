			printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(oid.hash, DEFAULT_ABBREV));
		}
		delete_branch_config(bname.buf);

	next:
		free(target);
	}

	free(name);

	return(ret);
}

static int calc_maxwidth(struct ref_array *refs, int remote_bonus)
{
	int i, max = 0;
	for (i = 0; i < refs->nr; i++) {
		struct ref_array_item *it = refs->items[i];
		const char *desc = it->refname;
		int w;

		skip_prefix(it->refname, "refs/heads/", &desc);
		skip_prefix(it->refname, "refs/remotes/", &desc);
		if (it->kind == FILTER_REFS_DETACHED_HEAD) {
			char *head_desc = get_head_description();
			w = utf8_strwidth(head_desc);
			free(head_desc);
		} else
			w = utf8_strwidth(desc);

		if (it->kind == FILTER_REFS_REMOTES)
			w += remote_bonus;
		if (w > max)
			max = w;
	}
	return max;
}

static const char *quote_literal_for_format(const char *s)
{
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	while (*s) {
		const char *ep = strchrnul(s, '%');
		if (s < ep)
			strbuf_add(&buf, s, ep - s);
		if (*ep == '%') {
			strbuf_addstr(&buf, "%%");
			s = ep + 1;
		} else {
			s = ep;
		}
	}
	return buf.buf;
}

static char *build_format(struct ref_filter *filter, int maxwidth, const char *remote_prefix)
{
	struct strbuf fmt = STRBUF_INIT;
	struct strbuf local = STRBUF_INIT;
	struct strbuf remote = STRBUF_INIT;

	strbuf_addf(&fmt, "%%(if)%%(HEAD)%%(then)* %s%%(else)  %%(end)",
		    branch_get_color(BRANCH_COLOR_CURRENT));

	if (filter->verbose) {
		struct strbuf obname = STRBUF_INIT;

		if (filter->abbrev < 0)
			strbuf_addf(&obname, "%%(objectname:short)");
		else if (!filter->abbrev)
			strbuf_addf(&obname, "%%(objectname)");
		else
			strbuf_addf(&obname, "%%(objectname:short=%d)", filter->abbrev);

		strbuf_addf(&local, "%%(align:%d,left)%%(refname:lstrip=2)%%(end)", maxwidth);
		strbuf_addf(&local, "%s", branch_get_color(BRANCH_COLOR_RESET));
		strbuf_addf(&local, " %s ", obname.buf);

		if (filter->verbose > 1)
			strbuf_addf(&local, "%%(if)%%(upstream)%%(then)[%s%%(upstream:short)%s%%(if)%%(upstream:track)"
				    "%%(then): %%(upstream:track,nobracket)%%(end)] %%(end)%%(contents:subject)",
				    branch_get_color(BRANCH_COLOR_UPSTREAM), branch_get_color(BRANCH_COLOR_RESET));
		else
			strbuf_addf(&local, "%%(if)%%(upstream:track)%%(then)%%(upstream:track) %%(end)%%(contents:subject)");

		strbuf_addf(&remote, "%s%%(align:%d,left)%s%%(refname:lstrip=2)%%(end)%s"
			    "%%(if)%%(symref)%%(then) -> %%(symref:short)"
			    "%%(else) %s %%(contents:subject)%%(end)",
			    branch_get_color(BRANCH_COLOR_REMOTE), maxwidth, quote_literal_for_format(remote_prefix),
			    branch_get_color(BRANCH_COLOR_RESET), obname.buf);
		strbuf_release(&obname);
	} else {
		strbuf_addf(&local, "%%(refname:lstrip=2)%s%%(if)%%(symref)%%(then) -> %%(symref:short)%%(end)",
			    branch_get_color(BRANCH_COLOR_RESET));
		strbuf_addf(&remote, "%s%s%%(refname:lstrip=2)%s%%(if)%%(symref)%%(then) -> %%(symref:short)%%(end)",
			    branch_get_color(BRANCH_COLOR_REMOTE), quote_literal_for_format(remote_prefix),
			    branch_get_color(BRANCH_COLOR_RESET));
	}

	strbuf_addf(&fmt, "%%(if:notequals=refs/remotes)%%(refname:rstrip=-2)%%(then)%s%%(else)%s%%(end)", local.buf, remote.buf);

	strbuf_release(&local);
	strbuf_release(&remote);
	return strbuf_detach(&fmt, NULL);
}

static void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting, const char *format)
{
	int i;
	struct ref_array array;
	int maxwidth = 0;
	const char *remote_prefix = "";
	struct strbuf out = STRBUF_INIT;
	char *to_free = NULL;

	/*
	 * If we are listing more than just remote branches,
	 * then remote branches will have a "remotes/" prefix.
	 * We need to account for this in the width.
	 */
	if (filter->kind != FILTER_REFS_REMOTES)
		remote_prefix = "remotes/";

	memset(&array, 0, sizeof(array));

	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	if (!format)
		format = to_free = build_format(filter, maxwidth, remote_prefix);
	verify_ref_format(format);

	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++) {
		format_ref_array_item(array.items[i], format, 0, &out);
		if (column_active(colopts)) {
			assert(!filter->verbose && "--column and --verbose are incompatible");
			 /* format to a string_list to let print_columns() do its job */
			string_list_append(&output, out.buf);
		} else {
			fwrite(out.buf, 1, out.len, stdout);
			putchar('\n');
		}
		strbuf_release(&out);
	}

	ref_array_clear(&array);
	free(to_free);
}

static void reject_rebase_or_bisect_branch(const char *target)
{
	struct worktree **worktrees = get_worktrees(0);
	int i;
