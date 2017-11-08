static int patch_id_cmp(struct diff_options *opt,
			struct patch_id *a,
			struct patch_id *b,
			const void *unused_keydata)
{
	if (is_null_oid(&a->patch_id) &&
	    commit_patch_id(a->commit, opt, &a->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&a->commit->object.oid));
	if (is_null_oid(&b->patch_id) &&
	    commit_patch_id(b->commit, opt, &b->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&b->commit->object.oid));
	return oidcmp(&a->patch_id, &b->patch_id);
}