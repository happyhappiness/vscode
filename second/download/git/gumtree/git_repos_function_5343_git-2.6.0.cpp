static void cmp_local_packs(void)
{
	struct pack_list *subset, *pl = local_packs;

	while ((subset = pl)) {
		while ((subset = subset->next))
			cmp_two_packs(pl, subset);
		pl = pl->next;
	}
}