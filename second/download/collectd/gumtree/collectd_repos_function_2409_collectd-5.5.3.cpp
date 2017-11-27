static void plugin_update_internal_statistics (void) { /* {{{ */
	derive_t copy_write_queue_length;
	value_list_t vl = VALUE_LIST_INIT;
	value_t values[2];

	copy_write_queue_length = write_queue_length;

	/* Initialize `vl' */
	vl.values = values;
	vl.values_len = 2;
	vl.time = 0;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "collectd", sizeof (vl.plugin));

	vl.type_instance[0] = 0;
	vl.values_len = 1;

	/* Write queue */
	sstrncpy (vl.plugin_instance, "write_queue",
			sizeof (vl.plugin_instance));

	/* Write queue : queue length */
	vl.values[0].gauge = (gauge_t) copy_write_queue_length;
	sstrncpy (vl.type, "queue_length", sizeof (vl.type));
	vl.type_instance[0] = 0;
	plugin_dispatch_values (&vl);

	/* Write queue : Values dropped (queue length > low limit) */
	vl.values[0].derive = (derive_t) stats_values_dropped;
	sstrncpy (vl.type, "derive", sizeof (vl.type));
	sstrncpy (vl.type_instance, "dropped", sizeof (vl.type_instance));
	plugin_dispatch_values (&vl);

	/* Cache */
	sstrncpy (vl.plugin_instance, "cache",
			sizeof (vl.plugin_instance));

	/* Cache : Nb entry in cache tree */
	vl.values[0].gauge = (gauge_t) uc_get_size();
	sstrncpy (vl.type, "cache_size", sizeof (vl.type));
	vl.type_instance[0] = 0;
	plugin_dispatch_values (&vl);

	return;
}