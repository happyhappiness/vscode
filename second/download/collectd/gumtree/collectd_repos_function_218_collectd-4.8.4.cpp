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
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "irq", sizeof (vl.plugin));
	sstrncpy (vl.type, "irq", sizeof (vl.type));

	status = ssnprintf (vl.type_instance, sizeof (vl.type_instance),
			"%u", irq);
	if ((status < 1) || ((unsigned int)status >= sizeof (vl.type_instance)))
		return;

	plugin_dispatch_values (&vl);
}