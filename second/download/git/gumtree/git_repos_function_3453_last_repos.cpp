int for_each_replace_ref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(get_main_ref_store(),
			       git_replace_ref_base, fn,
			       strlen(git_replace_ref_base),
			       0, cb_data);
}