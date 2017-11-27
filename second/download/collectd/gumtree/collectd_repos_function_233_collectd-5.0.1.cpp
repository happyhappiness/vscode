static int check_ignore_irq (const char *irq)
{
	unsigned int i;

	if (irq_list_num < 1)
		return (0);

	for (i = 0; i < irq_list_num; i++)
		if (strcmp (irq, irq_list[i]) == 0)
			return (irq_list_action);

	return (1 - irq_list_action);
}