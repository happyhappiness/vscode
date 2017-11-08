static void scan_alt_odb_packs(void)
{
	struct pack_list *local, *alt;

	alt = altodb_packs;
	while (alt) {
		local = local_packs;
		while (local) {
			llist_sorted_difference_inplace(local->unique_objects,
							alt->all_objects);
			local = local->next;
		}
		llist_sorted_difference_inplace(all_objects, alt->all_objects);
		alt = alt->next;
	}
}