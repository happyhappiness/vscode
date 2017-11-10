int twoway_merge(const struct cache_entry * const *src,
		 struct unpack_trees_options *o)
{
	const struct cache_entry *current = src[0];
	const struct cache_entry *oldtree = src[1];
	const struct cache_entry *newtree = src[2];

	if (o->merge_size != 2)
		return error("Cannot do a twoway merge of %d trees",
			     o->merge_size);

	if (oldtree == o->df_conflict_entry)
		oldtree = NULL;
	if (newtree == o->df_conflict_entry)
		newtree = NULL;

	if (current) {
		if (current->ce_flags & CE_CONFLICTED) {
			if (same(oldtree, newtree) || o->reset) {
				if (!newtree)
					return deleted_entry(current, current, o);
				else
					return merged_entry(newtree, current, o);
			}
			return reject_merge(current, o);
		} else if ((!oldtree && !newtree) || /* 4 and 5 */
			 (!oldtree && newtree &&
			  same(current, newtree)) || /* 6 and 7 */
			 (oldtree && newtree &&
			  same(oldtree, newtree)) || /* 14 and 15 */
			 (oldtree && newtree &&
			  !same(oldtree, newtree) && /* 18 and 19 */
			  same(current, newtree))) {
			return keep_entry(current, o);
		} else if (oldtree && !newtree && same(current, oldtree)) {
			/* 10 or 11 */
			return deleted_entry(oldtree, current, o);
		} else if (oldtree && newtree &&
			 same(current, oldtree) && !same(current, newtree)) {
			/* 20 or 21 */
			return merged_entry(newtree, current, o);
		} else
			return reject_merge(current, o);
	}
	else if (newtree) {
		if (oldtree && !o->initial_checkout) {
			/*
			 * deletion of the path was staged;
			 */
			if (same(oldtree, newtree))
				return 1;
			return reject_merge(oldtree, o);
		}
		return merged_entry(newtree, current, o);
	}
	return deleted_entry(oldtree, current, o);
}