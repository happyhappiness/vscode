int check_everything_connected(sha1_iterate_fn fn, int quiet, void *cb_data)
{
	return check_everything_connected_with_transport(fn, quiet, cb_data, NULL);
}