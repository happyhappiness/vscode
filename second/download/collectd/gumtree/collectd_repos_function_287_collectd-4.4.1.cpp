static void ps_list_register (const char *name)
{
	procstat_t *new;
	procstat_t *ptr;

	if ((new = (procstat_t *) malloc (sizeof (procstat_t))) == NULL)
		return;
	memset (new, 0, sizeof (procstat_t));
	strncpy (new->name, name, PROCSTAT_NAME_LEN);

	for (ptr = list_head_g; ptr != NULL; ptr = ptr->next)
	{
		if (strcmp (ptr->name, name) == 0)
			return;
		if (ptr->next == NULL)
			break;
	}

	if (ptr == NULL)
		list_head_g = new;
	else
		ptr->next = new;
}