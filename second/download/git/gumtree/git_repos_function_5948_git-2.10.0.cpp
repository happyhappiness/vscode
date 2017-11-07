int for_each_reflog(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref_iterator(files_reflog_iterator_begin(),
					fn, cb_data);
}