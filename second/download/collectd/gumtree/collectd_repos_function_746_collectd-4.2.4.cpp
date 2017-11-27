static int my_read (void)
{
	value_t values[1]; /* the size of this list should equal the number of
						  data sources */
	value_list_t vl = VALUE_LIST_INIT;

	/* do the magic to read the data */
	values[0].gauge = random ();

	vl.values     = values;
	vl.values_len = 1;
	vl.time       = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "myplugin");
	/* optionally set vl.plugin_instance and vl.type_instance to reasonable
	 * values (default: "") */

	/* dispatch the values to collectd which passes them on to all registered
	 * write functions - the first argument is used to lookup the data set
	 * definition */
	plugin_dispatch_values ("myplugin", &vl);

	/* A return value != 0 indicates an error and the plugin will be skipped
	 * for an increasing amount of time. */
    return 0;
}