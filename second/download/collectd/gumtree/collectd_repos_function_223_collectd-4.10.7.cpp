static int irq_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Irq") == 0)
	{
		char **temp;

		temp = realloc (irq_list, (irq_list_num + 1) * sizeof (*irq_list));
		if (temp == NULL)
		{
			fprintf (stderr, "irq plugin: Cannot allocate more memory.\n");
			ERROR ("irq plugin: Cannot allocate more memory.");
			return (1);
		}
		irq_list = temp;

		irq_list[irq_list_num] = strdup (value);
		if (irq_list[irq_list_num] == NULL)
		{
			ERROR ("irq plugin: strdup(3) failed.");
			return (1);
		}

		irq_list_num++;
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		if (IS_TRUE (value))
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