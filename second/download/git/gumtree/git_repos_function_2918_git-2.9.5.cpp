int for_each_fullref_in(const char *prefix, each_ref_fn fn, void *cb_data, unsigned int broken)
{
	unsigned int flag = 0;

	if (broken)
		flag = DO_FOR_EACH_INCLUDE_BROKEN;
	return do_for_each_ref(NULL, prefix, fn, 0, flag, cb_data);
}