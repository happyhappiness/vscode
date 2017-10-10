	error("%s", err.buf);
	strbuf_release(&err);
	return df_conflict ? STORE_REF_ERROR_DF_CONFLICT
			   : STORE_REF_ERROR_OTHER;
}

static int refcol_width = 10;
static int compact_format;

static void adjust_refcol_width(const struct ref *ref)
{
	int max, rlen, llen, len;

	/* uptodate lines are only shown on high verbosity level */
	if (!verbosity && !oidcmp(&ref->peer_ref->old_oid, &ref->old_oid))
		return;

	max    = term_columns();
	rlen   = utf8_strwidth(prettify_refname(ref->name));

	llen   = utf8_strwidth(prettify_refname(ref->peer_ref->name));

	/*
	 * rough estimation to see if the output line is too long and
	 * should not be counted (we can't do precise calculation
	 * anyway because we don't know if the error explanation part
	 * will be printed in update_local_ref)
	 */
	if (compact_format) {
		llen = 0;
		max = max * 2 / 3;
	}
	len = 21 /* flag and summary */ + rlen + 4 /* -> */ + llen;
	if (len >= max)
		return;

	/*
	 * Not precise calculation for compact mode because '*' can
	 * appear on the left hand side of '->' and shrink the column
	 * back.
	 */
	if (refcol_width < rlen)
		refcol_width = rlen;
}

static void prepare_format_display(struct ref *ref_map)
{
	struct ref *rm;
	const char *format = "full";

	git_config_get_string_const("fetch.output", &format);
	if (!strcasecmp(format, "full"))
		compact_format = 0;
	else if (!strcasecmp(format, "compact"))
		compact_format = 1;
	else
		die(_("configuration fetch.output contains invalid value %s"),
		    format);

	for (rm = ref_map; rm; rm = rm->next) {
		if (rm->status == REF_STATUS_REJECT_SHALLOW ||
		    !rm->peer_ref ||
		    !strcmp(rm->name, "HEAD"))
			continue;

		adjust_refcol_width(rm);
	}
}

static void print_remote_to_local(struct strbuf *display,
				  const char *remote, const char *local)
{
	strbuf_addf(display, "%-*s -> %s", refcol_width, remote, local);
}

static int find_and_replace(struct strbuf *haystack,
			    const char *needle,
			    const char *placeholder)
{
	const char *p = strstr(haystack->buf, needle);
	int plen, nlen;

	if (!p)
		return 0;

	if (p > haystack->buf && p[-1] != '/')
		return 0;

	plen = strlen(p);
	nlen = strlen(needle);
	if (plen > nlen && p[nlen] != '/')
		return 0;

	strbuf_splice(haystack, p - haystack->buf, nlen,
		      placeholder, strlen(placeholder));
	return 1;
}

static void print_compact(struct strbuf *display,
			  const char *remote, const char *local)
{
	struct strbuf r = STRBUF_INIT;
	struct strbuf l = STRBUF_INIT;

	if (!strcmp(remote, local)) {
		strbuf_addf(display, "%-*s -> *", refcol_width, remote);
		return;
	}

	strbuf_addstr(&r, remote);
	strbuf_addstr(&l, local);

	if (!find_and_replace(&r, local, "*"))
		find_and_replace(&l, remote, "*");
	print_remote_to_local(display, r.buf, l.buf);

	strbuf_release(&r);
	strbuf_release(&l);
}

static void format_display(struct strbuf *display, char code,
			   const char *summary, const char *error,
			   const char *remote, const char *local)
{
	strbuf_addf(display, "%c %-*s ", code, TRANSPORT_SUMMARY(summary));
	if (!compact_format)
		print_remote_to_local(display, remote, local);
	else
		print_compact(display, remote, local);
	if (error)
		strbuf_addf(display, "  (%s)", error);
}

static int update_local_ref(struct ref *ref,
			    const char *remote,
			    const struct ref *remote_ref,
			    struct strbuf *display)
{
