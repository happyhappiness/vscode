struct patch_id *has_commit_patch_id(struct commit *commit,
				     struct patch_ids *ids)
{
	struct patch_id patch;

	memset(&patch, 0, sizeof(patch));
	if (init_patch_id_entry(&patch, commit, ids))
		return NULL;

	return hashmap_get(&ids->patches, &patch, &ids->diffopts);
}