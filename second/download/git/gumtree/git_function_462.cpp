static int append_ref(const char *refname, const struct object_id *oid,
		      int allow_dups)
{
	struct commit *commit = lookup_commit_reference_gently(oid->hash, 1);
	int i;

	if (!commit)
		return 0;

	if (!allow_dups) {
		/* Avoid adding the same thing twice */
		for (i = 0; i < ref_name_cnt; i++)
			if (!strcmp(refname, ref_name[i]))
				return 0;
	}
	if (MAX_REVS <= ref_name_cnt) {
		warning("ignoring %s; cannot handle more than %d refs",
			refname, MAX_REVS);
		return 0;
	}
	ref_name[ref_name_cnt++] = xstrdup(refname);
	ref_name[ref_name_cnt] = NULL;
	return 0;
}