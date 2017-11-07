static int do_for_each_ref(struct ref_cache *refs, const char *base,
			   each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_entry_cb data;
	data.base = base;
	data.trim = trim;
	data.flags = flags;
	data.fn = fn;
	data.cb_data = cb_data;

	return do_for_each_entry(refs, base, do_one_ref, &data);
}