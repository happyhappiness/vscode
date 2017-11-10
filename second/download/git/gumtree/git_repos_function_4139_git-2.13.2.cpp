int for_each_abbrev(const char *prefix, each_abbrev_fn fn, void *cb_data)
{
	struct oid_array collect = OID_ARRAY_INIT;
	struct disambiguate_state ds;
	int ret;

	if (init_object_disambiguation(prefix, strlen(prefix), &ds) < 0)
		return -1;

	ds.always_call_fn = 1;
	ds.fn = collect_ambiguous;
	ds.cb_data = &collect;
	find_short_object_filename(&ds);
	find_short_packed_object(&ds);

	ret = oid_array_for_each_unique(&collect, fn, cb_data);
	oid_array_clear(&collect);
	return ret;
}