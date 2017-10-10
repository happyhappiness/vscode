}

int expand_ref(const char *str, int len, unsigned char *sha1, char **ref)
{
	const char **p, *r;
	int refs_found = 0;
	struct strbuf fullref = STRBUF_INIT;

	*ref = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		unsigned char sha1_from_ref[20];
		unsigned char *this_result;
		int flag;

		this_result = refs_found ? sha1_from_ref : sha1;
		strbuf_reset(&fullref);
		strbuf_addf(&fullref, *p, len, str);
		r = resolve_ref_unsafe(fullref.buf, RESOLVE_REF_READING,
				       this_result, &flag);
		if (r) {
			if (!refs_found++)
				*ref = xstrdup(r);
			if (!warn_ambiguous_refs)
				break;
		} else if ((flag & REF_ISSYMREF) && strcmp(fullref.buf, "HEAD")) {
			warning("ignoring dangling symref %s.", fullref.buf);
		} else if ((flag & REF_ISBROKEN) && strchr(fullref.buf, '/')) {
			warning("ignoring broken ref %s.", fullref.buf);
		}
	}
	strbuf_release(&fullref);
	return refs_found;
}

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

static int is_per_worktree_ref(const char *refname)
{
