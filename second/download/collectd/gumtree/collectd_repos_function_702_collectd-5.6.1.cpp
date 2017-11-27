static void mic_submit_memory_use(int micnumber, const char *type_instance, U32 val)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	/* MicAccessAPI reports KB's of memory, adjust for this */
	DEBUG("mic plugin: Memory Value Report; %u %lf",val,((gauge_t)val)*1024.0);
	values[0].gauge = ((gauge_t)val)*1024.0;

	vl.values=values;
	vl.values_len=1;

	strncpy (vl.host, hostname_g, sizeof (vl.host));
	strncpy (vl.plugin, "mic", sizeof (vl.plugin));
	ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance), "%i", micnumber);
	strncpy (vl.type, "memory", sizeof (vl.type));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}