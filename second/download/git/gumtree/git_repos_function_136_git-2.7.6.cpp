int check_everything_connected_with_transport(sha1_iterate_fn fn,
					      int quiet,
					      void *cb_data,
					      struct transport *transport)
{
	return check_everything_connected_real(fn, quiet, cb_data,
					       transport, NULL);
}