static void ps_list_reset (void)
{
	procstat_entry_t *pse;
	procstat_entry_t *pse_prev;

	for (procstat_t *ps = list_head_g; ps != NULL; ps = ps->next)
	{
		ps->num_proc    = 0;
		ps->num_lwp     = 0;
		ps->vmem_size   = 0;
		ps->vmem_rss    = 0;
		ps->vmem_data   = 0;
		ps->vmem_code   = 0;
		ps->stack_size  = 0;
		ps->io_rchar = -1;
		ps->io_wchar = -1;
		ps->io_syscr = -1;
		ps->io_syscw = -1;
		ps->cswitch_vol   = -1;
		ps->cswitch_invol = -1;

		pse_prev = NULL;
		pse = ps->instances;
		while (pse != NULL)
		{
			if (pse->age > 10)
			{
				DEBUG ("Removing this procstat entry cause it's too old: "
						"id = %lu; name = %s;",
						pse->id, ps->name);

				if (pse_prev == NULL)
				{
					ps->instances = pse->next;
					free (pse);
					pse = ps->instances;
				}
				else
				{
					pse_prev->next = pse->next;
					free (pse);
					pse = pse_prev->next;
				}
			}
			else
			{
				pse->age++;
				pse_prev = pse;
				pse = pse->next;
			}
		} /* while (pse != NULL) */
	} /* for (ps = list_head_g; ps != NULL; ps = ps->next) */
}