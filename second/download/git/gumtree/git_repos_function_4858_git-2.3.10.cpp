static int prune_refs(struct refspec *refs, int ref_count, struct ref *ref_map,
		const char *raw_url)
{
	int url_len, i, result = 0;
	struct ref *ref, *stale_refs = get_stale_heads(refs, ref_count, ref_map);
	char *url;
	const char *dangling_msg = dry_run
		? _("   (%s will become dangling)")
		: _("   (%s has become dangling)");

	if (raw_url)
		url = transport_anonymize_url(raw_url);
	else
		url = xstrdup("foreign");

	url_len = strlen(url);
	for (i = url_len - 1; url[i] == '/' && 0 <= i; i--)
		;

	url_len = i + 1;
	if (4 < i && !strncmp(".git", url + i - 3, 4))
		url_len = i - 3;

	for (ref = stale_refs; ref; ref = ref->next) {
		if (!dry_run)
			result |= delete_ref(ref->name, NULL, 0);
		if (verbosity >= 0 && !shown_url) {
			fprintf(stderr, _("From %.*s\n"), url_len, url);
			shown_url = 1;
		}
		if (verbosity >= 0) {
			fprintf(stderr, " x %-*s %-*s -> %s\n",
				TRANSPORT_SUMMARY(_("[deleted]")),
				REFCOL_WIDTH, _("(none)"), prettify_refname(ref->name));
			warn_dangling_symref(stderr, dangling_msg, ref->name);
		}
	}
	free(url);
	free_refs(stale_refs);
	return result;
}