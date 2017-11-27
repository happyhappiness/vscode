static void thermal_submit (const char *plugin_instance, enum dev_type dt,
		gauge_t value)
{
	value_list_t vl = (dt == TEMP) ? vl_temp_template : vl_state_template;
	value_t vt;

	vt.gauge = value;

	vl.values = &vt;
	vl.time = time (NULL);
	sstrncpy (vl.plugin, "thermal", sizeof(vl.plugin));
	sstrncpy (vl.plugin_instance, plugin_instance,
			sizeof(vl.plugin_instance));
	sstrncpy (vl.type, (dt == TEMP) ? "temperature" : "gauge",
			sizeof (vl.type));

	plugin_dispatch_values (&vl);
}