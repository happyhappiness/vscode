	for_each_string_list_item(ref_to_delete, &refs_to_delete) {
		if (remove_entry(packed, ref_to_delete->string) == -1)
			die("internal error");
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret && err)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
}

static int repack_without_ref(const char *refname)
{
	return repack_without_refs(&refname, 1, NULL);
}

static int delete_ref_loose(struct ref_lock *lock, int flag)
{
	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
		/* loose */
