	int len;
	struct ref_entry *ref;

	if (check_name &&
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
		die("Reference has invalid format: '%s'", refname);
	if (!check_name && !refname_is_safe(refname))
		die("Reference has invalid name: '%s'", refname);
	len = strlen(refname) + 1;
	ref = xmalloc(sizeof(struct ref_entry) + len);
	hashcpy(ref->u.value.sha1, sha1);
	hashclr(ref->u.value.peeled);
	memcpy(ref->name, refname, len);
	ref->flag = flag;
	return ref;
}

static void clear_ref_dir(struct ref_dir *dir);
