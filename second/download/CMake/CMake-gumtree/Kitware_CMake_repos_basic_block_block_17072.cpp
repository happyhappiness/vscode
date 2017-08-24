{
	struct pax *pax;
	size_t ws;
	size_t total;
	int ret;

	pax = (struct pax *)a->format_data;

	/*
	 * According to GNU PAX format 1.0, write a sparse map
	 * before the body.
	 */
	if (archive_strlen(&(pax->sparse_map))) {
		ret = __archive_write_output(a, pax->sparse_map.s,
		    archive_strlen(&(pax->sparse_map)));
		if (ret != ARCHIVE_OK)
			return (ret);
		ret = __archive_write_nulls(a, pax->sparse_map_padding);
		if (ret != ARCHIVE_OK)
			return (ret);
		archive_string_empty(&(pax->sparse_map));
	}

	total = 0;
	while (total < s) {
		const unsigned char *p;

		while (pax->sparse_list != NULL &&
		    pax->sparse_list->remaining == 0) {
			struct sparse_block *sb = pax->sparse_list->next;
			free(pax->sparse_list);
			pax->sparse_list = sb;
		}

		if (pax->sparse_list == NULL)
			return (total);

		p = ((const unsigned char *)buff) + total;
		ws = s - total;
		if (ws > pax->sparse_list->remaining)
			ws = (size_t)pax->sparse_list->remaining;

		if (pax->sparse_list->is_hole) {
			/* Current block is hole thus we do not write
			 * the body. */
			pax->sparse_list->remaining -= ws;
			total += ws;
			continue;
		}

		ret = __archive_write_output(a, p, ws);
		pax->sparse_list->remaining -= ws;
		total += ws;
		if (ret != ARCHIVE_OK)
			return (ret);
	}
	return (total);
}