static void ps_list_add (const char *name, const char *cmdline, procstat_entry_t *entry)
{
	procstat_t *ps;
	procstat_entry_t *pse;

	if (entry->id == 0)
		return;

	for (ps = list_head_g; ps != NULL; ps = ps->next)
	{
		if ((ps_list_match (name, cmdline, ps)) == 0)
			continue;

		for (pse = ps->instances; pse != NULL; pse = pse->next)
			if ((pse->id == entry->id) || (pse->next == NULL))
				break;

		if ((pse == NULL) || (pse->id != entry->id))
		{
			procstat_entry_t *new;

			new = (procstat_entry_t *) malloc (sizeof (procstat_entry_t));
			if (new == NULL)
				return;
			memset (new, 0, sizeof (procstat_entry_t));
			new->id = entry->id;

			if (pse == NULL)
				ps->instances = new;
			else
				pse->next = new;

			pse = new;
		}

		pse->age = 0;
		pse->num_proc   = entry->num_proc;
		pse->num_lwp    = entry->num_lwp;
		pse->vmem_size  = entry->vmem_size;
		pse->vmem_rss   = entry->vmem_rss;
		pse->vmem_data  = entry->vmem_data;
		pse->vmem_code  = entry->vmem_code;
		pse->stack_size = entry->stack_size;
		pse->io_rchar   = entry->io_rchar;
		pse->io_wchar   = entry->io_wchar;
		pse->io_syscr   = entry->io_syscr;
		pse->io_syscw   = entry->io_syscw;

		ps->num_proc   += pse->num_proc;
		ps->num_lwp    += pse->num_lwp;
		ps->vmem_size  += pse->vmem_size;
		ps->vmem_rss   += pse->vmem_rss;
		ps->vmem_data  += pse->vmem_data;
		ps->vmem_code  += pse->vmem_code;
		ps->stack_size += pse->stack_size;

		ps->io_rchar   += ((pse->io_rchar == -1)?0:pse->io_rchar);
		ps->io_wchar   += ((pse->io_wchar == -1)?0:pse->io_wchar);
		ps->io_syscr   += ((pse->io_syscr == -1)?0:pse->io_syscr);
		ps->io_syscw   += ((pse->io_syscw == -1)?0:pse->io_syscw);

		if ((entry->vmem_minflt_counter == 0)
				&& (entry->vmem_majflt_counter == 0))
		{
			pse->vmem_minflt_counter += entry->vmem_minflt;
			pse->vmem_minflt = entry->vmem_minflt;

			pse->vmem_majflt_counter += entry->vmem_majflt;
			pse->vmem_majflt = entry->vmem_majflt;
		}
		else
		{
			if (entry->vmem_minflt_counter < pse->vmem_minflt_counter)
			{
				pse->vmem_minflt = entry->vmem_minflt_counter
					+ (ULONG_MAX - pse->vmem_minflt_counter);
			}
			else
			{
				pse->vmem_minflt = entry->vmem_minflt_counter - pse->vmem_minflt_counter;
			}
			pse->vmem_minflt_counter = entry->vmem_minflt_counter;

			if (entry->vmem_majflt_counter < pse->vmem_majflt_counter)
			{
				pse->vmem_majflt = entry->vmem_majflt_counter
					+ (ULONG_MAX - pse->vmem_majflt_counter);
			}
			else
			{
				pse->vmem_majflt = entry->vmem_majflt_counter - pse->vmem_majflt_counter;
			}
			pse->vmem_majflt_counter = entry->vmem_majflt_counter;
		}

		ps->vmem_minflt_counter += pse->vmem_minflt;
		ps->vmem_majflt_counter += pse->vmem_majflt;

		if ((entry->cpu_user_counter == 0)
				&& (entry->cpu_system_counter == 0))
		{
			pse->cpu_user_counter += entry->cpu_user;
			pse->cpu_user = entry->cpu_user;

			pse->cpu_system_counter += entry->cpu_system;
			pse->cpu_system = entry->cpu_system;
		}
		else
		{
			if (entry->cpu_user_counter < pse->cpu_user_counter)
			{
				pse->cpu_user = entry->cpu_user_counter
					+ (ULONG_MAX - pse->cpu_user_counter);
			}
			else
			{
				pse->cpu_user = entry->cpu_user_counter - pse->cpu_user_counter;
			}
			pse->cpu_user_counter = entry->cpu_user_counter;

			if (entry->cpu_system_counter < pse->cpu_system_counter)
			{
				pse->cpu_system = entry->cpu_system_counter
					+ (ULONG_MAX - pse->cpu_system_counter);
			}
			else
			{
				pse->cpu_system = entry->cpu_system_counter - pse->cpu_system_counter;
			}
			pse->cpu_system_counter = entry->cpu_system_counter;
		}

		ps->cpu_user_counter   += pse->cpu_user;
		ps->cpu_system_counter += pse->cpu_system;
	}
}