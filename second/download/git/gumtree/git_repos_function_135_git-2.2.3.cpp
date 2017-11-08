int check_shallow_connected(sha1_iterate_fn fn, int quiet, void *cb_data,
			    const char *shallow_file)
{
	return check_everything_connected_real(fn, quiet, cb_data,
					       NULL, shallow_file);
}