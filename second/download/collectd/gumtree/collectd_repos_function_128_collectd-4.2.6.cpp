static void irq_submit (unsigned int irq, counter_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;
	int status;

	if (check_ignore_irq (irq))
		return;

	values[0].counter = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "irq");

	status = snprintf (vl.type_instance, sizeof (vl.type_instance),
			"%u", irq);
	if ((status < 1) || (status >= sizeof (vl.type_instance)))
		return;

	plugin_dispatch_values ("irq", &vl);
}