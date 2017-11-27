static int irq_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Irq") == 0)
	{
		unsigned int *temp;
		unsigned int irq;
		char *endptr;

		temp = (unsigned int *) realloc (irq_list, (irq_list_num + 1) * sizeof (unsigned int *));
		if (temp == NULL)
		{
			fprintf (stderr, "irq plugin: Cannot allocate more memory.\n");
			ERROR ("irq plugin: Cannot allocate more memory.");
			return (1);
		}
		irq_list = temp;

		/* Clear errno, because we need it to see if an error occured. */
		errno = 0;

		irq = strtol(value, &endptr, 10);
		if ((endptr == value) || (errno != 0))
		{
			fprintf (stderr, "irq plugin: Irq value is not a "
					"number: `%s'\n", value);
			ERROR ("irq plugin: Irq value is not a "
					"number: `%s'", value);
			return (1);
		}
		irq_list[irq_list_num] = irq;
		irq_list_num++;
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			irq_list_action = 1;
		else
			irq_list_action = 0;
	}
	else
	{
		return (-1);
	}
	return (0);
}