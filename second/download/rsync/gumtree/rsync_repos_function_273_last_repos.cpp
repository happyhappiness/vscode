static int find_matching_xattr(item_list *xalp)
{
	size_t i, j;
	item_list *lst = rsync_xal_l.items;

	for (i = 0; i < rsync_xal_l.count; i++) {
		rsync_xa *rxas1 = lst[i].items;
		rsync_xa *rxas2 = xalp->items;

		/* Wrong number of elements? */
		if (lst[i].count != xalp->count)
			continue;
		/* any elements different? */
		for (j = 0; j < xalp->count; j++) {
			if (rxas1[j].name_len != rxas2[j].name_len
			 || rxas1[j].datum_len != rxas2[j].datum_len
			 || strcmp(rxas1[j].name, rxas2[j].name))
				break;
			if (rxas1[j].datum_len > MAX_FULL_DATUM) {
				if (memcmp(rxas1[j].datum + 1,
					   rxas2[j].datum + 1,
					   MAX_DIGEST_LEN) != 0)
					break;
			} else {
				if (memcmp(rxas1[j].datum, rxas2[j].datum,
					   rxas2[j].datum_len))
					break;
			}
		}
		/* no differences found.  This is The One! */
		if (j == xalp->count)
			return i;
	}

	return -1;
}