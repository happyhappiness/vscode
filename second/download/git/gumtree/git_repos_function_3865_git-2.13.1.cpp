struct patch_id *add_commit_patch_id(struct commit *commit,
				     struct patch_ids *ids)
{
	struct patch_id *key;

	if (!patch_id_defined(commit))
		return NULL;

	key = xcalloc(1, sizeof(*key));
	if (init_patch_id_entry(key, commit, ids)) {
		free(key);
		return NULL;
	}

	hashmap_add(&ids->patches, key);
	return key;
}