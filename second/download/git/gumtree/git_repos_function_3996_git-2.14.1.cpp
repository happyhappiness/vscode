int init_patch_ids(struct patch_ids *ids)
{
	memset(ids, 0, sizeof(*ids));
	diff_setup(&ids->diffopts);
	ids->diffopts.detect_rename = 0;
	DIFF_OPT_SET(&ids->diffopts, RECURSIVE);
	diff_setup_done(&ids->diffopts);
	hashmap_init(&ids->patches, (hashmap_cmp_fn)patch_id_cmp,
		     &ids->diffopts, 256);
	return 0;
}