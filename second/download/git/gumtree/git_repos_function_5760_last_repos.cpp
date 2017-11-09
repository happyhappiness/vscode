static int quickfetch(struct ref *ref_map)
{
	struct ref *rm = ref_map;
	struct check_connected_options opt = CHECK_CONNECTED_INIT;

	/*
	 * If we are deepening a shallow clone we already have these
	 * objects reachable.  Running rev-list here will return with
	 * a good (0) exit status and we'll bypass the fetch that we
	 * really need to perform.  Claiming failure now will ensure
	 * we perform the network exchange to deepen our history.
	 */
	if (deepen)
		return -1;
	opt.quiet = 1;
	return check_connected(iterate_ref_map, &rm, &opt);
}