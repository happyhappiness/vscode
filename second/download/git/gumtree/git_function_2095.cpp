static int grab_single_ref(const char *refname, const struct object_id *oid,
			   int flag, void *cb_data)
{
	struct grab_ref_cbdata *cb = cb_data;
	struct refinfo *ref;
	int cnt;

	if (flag & REF_BAD_NAME) {
		  warning("ignoring ref with broken name %s", refname);
		  return 0;
	}

	if (flag & REF_ISBROKEN) {
		  warning("ignoring broken ref %s", refname);
		  return 0;
	}

	if (*cb->grab_pattern) {
		const char **pattern;
		int namelen = strlen(refname);
		for (pattern = cb->grab_pattern; *pattern; pattern++) {
			const char *p = *pattern;
			int plen = strlen(p);

			if ((plen <= namelen) &&
			    !strncmp(refname, p, plen) &&
			    (refname[plen] == '\0' ||
			     refname[plen] == '/' ||
			     p[plen-1] == '/'))
				break;
			if (!wildmatch(p, refname, WM_PATHNAME, NULL))
				break;
		}
		if (!*pattern)
			return 0;
	}

	/*
	 * We do not open the object yet; sort may only need refname
	 * to do its job and the resulting list may yet to be pruned
	 * by maxcount logic.
	 */
	ref = xcalloc(1, sizeof(*ref));
	ref->refname = xstrdup(refname);
	hashcpy(ref->objectname, oid->hash);
	ref->flag = flag;

	cnt = cb->grab_cnt;
	REALLOC_ARRAY(cb->grab_array, cnt + 1);
	cb->grab_array[cnt++] = ref;
	cb->grab_cnt = cnt;
	return 0;
}