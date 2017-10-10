		read_loose_refs(entry->name, dir);
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}

/*
 * Check if a refname is safe.
 * For refs that start with "refs/" we consider it safe as long they do
 * not try to resolve to outside of refs/.
 *
 * For all other refs we only consider them safe iff they only contain
 * upper case characters and '_' (like "HEAD" AND "MERGE_HEAD", and not like
 * "config").
 */
static int refname_is_safe(const char *refname)
{
	if (starts_with(refname, "refs/")) {
		char *buf;
		int result;

		buf = xmalloc(strlen(refname) + 1);
		/*
		 * Does the refname try to escape refs/?
		 * For example: refs/foo/../bar is safe but refs/foo/../../bar
		 * is not.
		 */
		result = !normalize_path_copy(buf, refname + strlen("refs/"));
		free(buf);
		return result;
	}
	while (*refname) {
		if (!isupper(*refname) && *refname != '_')
			return 0;
		refname++;
	}
	return 1;
}

static struct ref_entry *create_ref_entry(const char *refname,
					  const unsigned char *sha1, int flag,
					  int check_name)
{
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
