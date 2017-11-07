static int patch_id_cmp(struct patch_id *a,
			struct patch_id *b,
			struct diff_options *opt)
{
	if (is_null_sha1(a->patch_id) &&
	    commit_patch_id(a->commit, opt, a->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&a->commit->object.oid));
	if (is_null_sha1(b->patch_id) &&
	    commit_patch_id(b->commit, opt, b->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&b->commit->object.oid));
	return hashcmp(a->patch_id, b->patch_id);
}