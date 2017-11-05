static struct patch_id *add_commit(struct commit *commit,
				   struct patch_ids *ids,
				   int no_add)
{
	struct patch_id_bucket *bucket;
	struct patch_id *ent;
	unsigned char sha1[20];
	int pos;

	if (commit_patch_id(commit, &ids->diffopts, sha1))
		return NULL;
	pos = patch_pos(ids->table, ids->nr, sha1);
	if (0 <= pos)
		return ids->table[pos];
	if (no_add)
		return NULL;

	pos = -1 - pos;

	bucket = ids->patches;
	if (!bucket || (BUCKET_SIZE <= bucket->nr)) {
		bucket = xcalloc(1, sizeof(*bucket));
		bucket->next = ids->patches;
		ids->patches = bucket;
	}
	ent = &bucket->bucket[bucket->nr++];
	hashcpy(ent->patch_id, sha1);

	ALLOC_GROW(ids->table, ids->nr + 1, ids->alloc);
	if (pos < ids->nr)
		memmove(ids->table + pos + 1, ids->table + pos,
			sizeof(ent) * (ids->nr - pos));
	ids->nr++;
	ids->table[pos] = ent;
	return ids->table[pos];
}