		}
		string_list_append(hide_refs, ref);
	}
	return 0;
}

int ref_is_hidden(const char *refname, const char *refname_full)
{
	int i;

	if (!hide_refs)
		return 0;
	for (i = hide_refs->nr - 1; i >= 0; i--) {
		const char *match = hide_refs->items[i].string;
		const char *subject;
		int neg = 0;
		int len;

		if (*match == '!') {
			neg = 1;
			match++;
		}

		if (*match == '^') {
			subject = refname_full;
			match++;
		} else {
			subject = refname;
		}

		/* refname can be NULL when namespaces are used. */
		if (!subject || !starts_with(subject, match))
			continue;
		len = strlen(match);
		if (!subject[len] || subject[len] == '/')
			return !neg;
	}
	return 0;
}

const char *find_descendant_ref(const char *dirname,
				const struct string_list *extras,
				const struct string_list *skip)
{
	int pos;

	if (!extras)
		return NULL;

	/*
	 * Look at the place where dirname would be inserted into
	 * extras. If there is an entry at that position that starts
	 * with dirname (remember, dirname includes the trailing
	 * slash) and is not in skip, then we have a conflict.
	 */
	for (pos = string_list_find_insert_index(extras, dirname, 0);
	     pos < extras->nr; pos++) {
		const char *extra_refname = extras->items[pos].string;

		if (!starts_with(extra_refname, dirname))
			break;

		if (!skip || !string_list_has_string(skip, extra_refname))
			return extra_refname;
	}
	return NULL;
}

int rename_ref_available(const char *oldname, const char *newname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	struct strbuf err = STRBUF_INIT;
	int ret;

	string_list_insert(&skip, oldname);
	ret = !verify_refname_available(newname, NULL, &skip, &err);
	if (!ret)
		error("%s", err.buf);

	string_list_clear(&skip, 0);
	strbuf_release(&err);
	return ret;
}
