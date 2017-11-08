struct object_entry *packlist_find(struct packing_data *pdata,
				   const unsigned char *sha1,
				   uint32_t *index_pos)
{
	uint32_t i;
	int found;

	if (!pdata->index_size)
		return NULL;

	i = locate_object_entry_hash(pdata, sha1, &found);

	if (index_pos)
		*index_pos = i;

	if (!found)
		return NULL;

	return &pdata->objects[pdata->index[i] - 1];
}