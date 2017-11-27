static void cr_submit_io (cr_data_t *rd, const char *type, /* {{{ */
    const char *type_instance, derive_t rx, derive_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = rx;
	values[1].derive = tx;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	sstrncpy (vl.host, rd->node, sizeof (vl.host));
	sstrncpy (vl.plugin, "routeros", sizeof (vl.plugin));
	sstrncpy (vl.type, type, sizeof (vl.type));
	sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}