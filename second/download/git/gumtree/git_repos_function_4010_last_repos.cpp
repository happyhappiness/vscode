int free_patch_ids(struct patch_ids *ids)
{
	hashmap_free(&ids->patches, 1);
	return 0;
}