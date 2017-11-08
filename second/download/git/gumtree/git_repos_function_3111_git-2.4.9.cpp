int free_patch_ids(struct patch_ids *ids)
{
	struct patch_id_bucket *next, *patches;

	free(ids->table);
	for (patches = ids->patches; patches; patches = next) {
		next = patches->next;
		free(patches);
	}
	return 0;
}