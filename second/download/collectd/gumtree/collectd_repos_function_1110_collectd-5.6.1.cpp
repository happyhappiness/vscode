static void cna_handle_volume_snap_usage(const host_config_t *host, /* {{{ */
		data_volume_usage_t *v)
{
	uint64_t snap_used = 0, value;
	na_elem_t *data, *elem_snapshots;
	na_elem_iter_t iter_snap;

	data = na_server_invoke_elem(host->srv, v->snap_query);
	if (na_results_status(data) != NA_OK)
	{
		if (na_results_errno(data) == EVOLUMEOFFLINE) {
			if ((v->flags & IS_VOLUME_USAGE_OFFLINE) == 0)
				cna_change_volume_status (host->name, v);
		} else {
			ERROR ("netapp plugin: cna_handle_volume_snap_usage: na_server_invoke_elem for "
					"volume \"%s\" on host %s failed with error %d: %s", v->name,
					host->name, na_results_errno(data), na_results_reason(data));
		}
		na_elem_free(data);
		return;
	}

	if ((v->flags & IS_VOLUME_USAGE_OFFLINE) != 0)
		cna_change_volume_status (host->name, v);

	elem_snapshots = na_elem_child (data, "snapshots");
	if (elem_snapshots == NULL)
	{
		ERROR ("netapp plugin: cna_handle_volume_snap_usage: "
				"na_elem_child (\"snapshots\") failed "
				"for host %s.", host->name);
		na_elem_free(data);
		return;
	}

	iter_snap = na_child_iterator (elem_snapshots);
	for (na_elem_t *elem_snap = na_iterator_next (&iter_snap);
			elem_snap != NULL;
			elem_snap = na_iterator_next (&iter_snap))
	{
		value = na_child_get_uint64(elem_snap, "cumulative-total", 0);
		/* "cumulative-total" is the total size of the oldest snapshot plus all
		 * newer ones in blocks (1KB). We therefore are looking for the highest
		 * number of all snapshots - that's the size required for the snapshots. */
		if (value > snap_used)
			snap_used = value;
	}
	na_elem_free (data);
	/* snap_used is in 1024 byte blocks */
	v->snap_used = snap_used * 1024;
	v->flags |= HAVE_VOLUME_USAGE_SNAP_USED;
}