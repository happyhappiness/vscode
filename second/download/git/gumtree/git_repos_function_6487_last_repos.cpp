struct ref_iterator *prefix_ref_iterator_begin(struct ref_iterator *iter0,
					       const char *prefix,
					       int trim)
{
	struct prefix_ref_iterator *iter;
	struct ref_iterator *ref_iterator;

	if (!*prefix && !trim)
		return iter0; /* optimization: no need to wrap iterator */

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;

	base_ref_iterator_init(ref_iterator, &prefix_ref_iterator_vtable);

	iter->iter0 = iter0;
	iter->prefix = xstrdup(prefix);
	iter->trim = trim;

	return ref_iterator;
}