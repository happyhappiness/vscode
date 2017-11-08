static uint32_t locate_object_entry_hash(struct packing_data *pdata,
					 const unsigned char *sha1,
					 int *found)
{
	uint32_t i, mask = (pdata->index_size - 1);

	i = sha1hash(sha1) & mask;

	while (pdata->index[i] > 0) {
		uint32_t pos = pdata->index[i] - 1;

		if (!hashcmp(sha1, pdata->objects[pos].idx.sha1)) {
			*found = 1;
			return i;
		}

		i = (i + 1) & mask;
	}

	*found = 0;
	return i;
}