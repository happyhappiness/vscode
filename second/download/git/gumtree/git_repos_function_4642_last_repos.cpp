static int tip_oids_contain(struct oidset *tip_oids,
			    struct ref *unmatched, struct ref *newlist,
			    const struct object_id *id)
{
	/*
	 * Note that this only looks at the ref lists the first time it's
	 * called. This works out in filter_refs() because even though it may
	 * add to "newlist" between calls, the additions will always be for
	 * oids that are already in the set.
	 */
	if (!tip_oids->map.tablesize) {
		add_refs_to_oidset(tip_oids, unmatched);
		add_refs_to_oidset(tip_oids, newlist);
	}
	return oidset_contains(tip_oids, id);
}