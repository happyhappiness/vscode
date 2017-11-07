int bind_merge(const struct cache_entry * const *src,
	       struct unpack_trees_options *o)
{
	const struct cache_entry *old = src[0];
	const struct cache_entry *a = src[1];

	if (o->merge_size != 1)
		return error("Cannot do a bind merge of %d trees",
			     o->merge_size);
	if (a && old)
		return o->gently ? -1 :
			error(ERRORMSG(o, ERROR_BIND_OVERLAP), a->name, old->name);
	if (!a)
		return keep_entry(old, o);
	else
		return merged_entry(a, NULL, o);
}