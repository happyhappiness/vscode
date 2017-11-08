static void minimize(struct pack_list **min)
{
	struct pack_list *pl, *unique = NULL,
		*non_unique = NULL, *min_perm = NULL;
	struct pll *perm, *perm_all, *perm_ok = NULL, *new_perm;
	struct llist *missing;
	off_t min_perm_size = 0, perm_size;
	int n;

	pl = local_packs;
	while (pl) {
		if (pl->unique_objects->size)
			pack_list_insert(&unique, pl);
		else
			pack_list_insert(&non_unique, pl);
		pl = pl->next;
	}
	/* find out which objects are missing from the set of unique packs */
	missing = llist_copy(all_objects);
	pl = unique;
	while (pl) {
		llist_sorted_difference_inplace(missing, pl->all_objects);
		pl = pl->next;
	}

	/* return if there are no objects missing from the unique set */
	if (missing->size == 0) {
		*min = unique;
		return;
	}

	/* find the permutations which contain all missing objects */
	for (n = 1; n <= pack_list_size(non_unique) && !perm_ok; n++) {
		perm_all = perm = get_permutations(non_unique, n);
		while (perm) {
			if (is_superset(perm->pl, missing)) {
				new_perm = xmalloc(sizeof(struct pll));
				memcpy(new_perm, perm, sizeof(struct pll));
				new_perm->next = perm_ok;
				perm_ok = new_perm;
			}
			perm = perm->next;
		}
		if (perm_ok)
			break;
		pll_free(perm_all);
	}
	if (perm_ok == NULL)
		die("Internal error: No complete sets found!");

	/* find the permutation with the smallest size */
	perm = perm_ok;
	while (perm) {
		perm_size = pack_set_bytecount(perm->pl);
		if (!min_perm_size || min_perm_size > perm_size) {
			min_perm_size = perm_size;
			min_perm = perm->pl;
		}
		perm = perm->next;
	}
	*min = min_perm;
	/* add the unique packs to the list */
	pl = unique;
	while (pl) {
		pack_list_insert(min, pl);
		pl = pl->next;
	}
}