
	vl.values     = values;
	vl.values_len = 1;
	vl.time       = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "myplugin", sizeof (vl.plugin));
	/* optionally set vl.plugin_instance and vl.type_instance to reasonable
	 * values (default: "") */

	/* dispatch the values to collectd which passes them on to all registered
	 * write functions - the first argument is used to lookup the data set
	 * definition (it is strongly recommended to use a type defined in the
	 * types.db file) */
	plugin_dispatch_values ("myplugin", &vl);

	/* A return value != 0 indicates an error and the plugin will be skipped
	 * for an increasing amount of time. */
    return 0;
} /* static int my_read (void) */

/*
 * This function is called after values have been dispatched to collectd.
 */
static int my_write (const data_set_t *ds, const value_list_t *vl)
{
	char name[1024] = "";
	int i = 0;

	if (ds->ds_num != vl->values_len) {
		plugin_log (LOG_WARNING, "DS number does not match values length");
