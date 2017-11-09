int dwim_log(const char *str, int len, unsigned char *sha1, char **log)
{
	char *last_branch = substitute_branch_name(&str, &len);
	const char **p;
	int logs_found = 0;
	struct strbuf path = STRBUF_INIT;

	*log = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		unsigned char hash[20];
		const char *ref, *it;

		strbuf_reset(&path);
		strbuf_addf(&path, *p, len, str);
		ref = resolve_ref_unsafe(path.buf, RESOLVE_REF_READING,
					 hash, NULL);
		if (!ref)
			continue;
		if (reflog_exists(path.buf))
			it = path.buf;
		else if (strcmp(ref, path.buf) && reflog_exists(ref))
			it = ref;
		else
			continue;
		if (!logs_found++) {
			*log = xstrdup(it);
			hashcpy(sha1, hash);
		}
		if (!warn_ambiguous_refs)
			break;
	}
	strbuf_release(&path);
	free(last_branch);
	return logs_found;
}