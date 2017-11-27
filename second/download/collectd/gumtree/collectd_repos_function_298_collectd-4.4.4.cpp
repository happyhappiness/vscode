static int ps_read (void)
{
#if HAVE_THREAD_INFO
	kern_return_t            status;

	int                      pset;
	processor_set_t          port_pset_priv;

	int                      task;
	task_array_t             task_list;
	mach_msg_type_number_t   task_list_len;

	int                      task_pid;
	char                     task_name[MAXCOMLEN + 1];

	int                      thread;
	thread_act_array_t       thread_list;
	mach_msg_type_number_t   thread_list_len;
	thread_basic_info_data_t thread_data;
	mach_msg_type_number_t   thread_data_len;

	int running  = 0;
	int sleeping = 0;
	int zombies  = 0;
	int stopped  = 0;
	int blocked  = 0;

	procstat_t *ps;
	procstat_entry_t pse;

	ps_list_reset ();

	/*
	 * The Mach-concept is a little different from the traditional UNIX
	 * concept: All the work is done in threads. Threads are contained in
	 * `tasks'. Therefore, `task status' doesn't make much sense, since
	 * it's actually a `thread status'.
	 * Tasks are assigned to sets of processors, so that's where you go to
	 * get a list.
	 */
	for (pset = 0; pset < pset_list_len; pset++)
	{
		if ((status = host_processor_set_priv (port_host_self,
						pset_list[pset],
						&port_pset_priv)) != KERN_SUCCESS)
		{
			ERROR ("host_processor_set_priv failed: %s\n",
					mach_error_string (status));
			continue;
		}

		if ((status = processor_set_tasks (port_pset_priv,
						&task_list,
						&task_list_len)) != KERN_SUCCESS)
		{
			ERROR ("processor_set_tasks failed: %s\n",
					mach_error_string (status));
			mach_port_deallocate (port_task_self, port_pset_priv);
			continue;
		}

		for (task = 0; task < task_list_len; task++)
		{
			ps = NULL;
			if (mach_get_task_name (task_list[task],
						&task_pid,
						task_name, PROCSTAT_NAME_LEN) == 0)
				ps = ps_list_search (task_name);

			/* Collect more detailed statistics for this process */
			if (ps != NULL)
			{
				task_basic_info_data_t        task_basic_info;
				mach_msg_type_number_t        task_basic_info_len;
				task_events_info_data_t       task_events_info;
				mach_msg_type_number_t        task_events_info_len;
				task_absolutetime_info_data_t task_absolutetime_info;
				mach_msg_type_number_t        task_absolutetime_info_len;

				memset (&pse, '\0', sizeof (pse));
				pse.id = task_pid;

				task_basic_info_len = TASK_BASIC_INFO_COUNT;
				status = task_info (task_list[task],
						TASK_BASIC_INFO,
						(task_info_t) &task_basic_info,
						&task_basic_info_len);
				if (status != KERN_SUCCESS)
				{
					ERROR ("task_info failed: %s",
							mach_error_string (status));
					continue; /* with next thread_list */
				}

				task_events_info_len = TASK_EVENTS_INFO_COUNT;
				status = task_info (task_list[task],
						TASK_EVENTS_INFO,
						(task_info_t) &task_events_info,
						&task_events_info_len);
				if (status != KERN_SUCCESS)
				{
					ERROR ("task_info failed: %s",
							mach_error_string (status));
					continue; /* with next thread_list */
				}

				task_absolutetime_info_len = TASK_ABSOLUTETIME_INFO_COUNT;
				status = task_info (task_list[task],
						TASK_ABSOLUTETIME_INFO,
						(task_info_t) &task_absolutetime_info,
						&task_absolutetime_info_len);
				if (status != KERN_SUCCESS)
				{
					ERROR ("task_info failed: %s",
							mach_error_string (status));
					continue; /* with next thread_list */
				}

				pse.num_proc++;
				pse.vmem_rss = task_basic_info.resident_size;

				pse.vmem_minflt_counter = task_events_info.cow_faults;
				pse.vmem_majflt_counter = task_events_info.faults;

				pse.cpu_user_counter = task_absolutetime_info.total_user;
				pse.cpu_system_counter = task_absolutetime_info.total_system;
			}

			status = task_threads (task_list[task], &thread_list,
					&thread_list_len);
			if (status != KERN_SUCCESS)
			{
				/* Apple's `top' treats this case a zombie. It
				 * makes sense to some extend: A `zombie'
				 * thread is nonsense, since the task/process
				 * is dead. */
				zombies++;
				DEBUG ("task_threads failed: %s",
						mach_error_string (status));
				if (task_list[task] != port_task_self)
					mach_port_deallocate (port_task_self,
							task_list[task]);
				continue; /* with next task_list */
			}

			for (thread = 0; thread < thread_list_len; thread++)
			{
				thread_data_len = THREAD_BASIC_INFO_COUNT;
				status = thread_info (thread_list[thread],
						THREAD_BASIC_INFO,
						(thread_info_t) &thread_data,
						&thread_data_len);
				if (status != KERN_SUCCESS)
				{
					ERROR ("thread_info failed: %s",
							mach_error_string (status));
					if (task_list[task] != port_task_self)
						mach_port_deallocate (port_task_self,
								thread_list[thread]);
					continue; /* with next thread_list */
				}

				if (ps != NULL)
					pse.num_lwp++;

				switch (thread_data.run_state)
				{
					case TH_STATE_RUNNING:
						running++;
						break;
					case TH_STATE_STOPPED:
					/* What exactly is `halted'? */
					case TH_STATE_HALTED:
						stopped++;
						break;
					case TH_STATE_WAITING:
						sleeping++;
						break;
					case TH_STATE_UNINTERRUPTIBLE:
						blocked++;
						break;
					/* There is no `zombie' case here,
					 * since there are no zombie-threads.
					 * There's only zombie tasks, which are
					 * handled above. */
					default:
						WARNING ("Unknown thread status: %i",
								thread_data.run_state);
						break;
				} /* switch (thread_data.run_state) */

				if (task_list[task] != port_task_self)
				{
					status = mach_port_deallocate (port_task_self,
							thread_list[thread]);
					if (status != KERN_SUCCESS)
						ERROR ("mach_port_deallocate failed: %s",
								mach_error_string (status));
				}
			} /* for (thread_list) */

			if ((status = vm_deallocate (port_task_self,
							(vm_address_t) thread_list,
							thread_list_len * sizeof (thread_act_t)))
					!= KERN_SUCCESS)
			{
				ERROR ("vm_deallocate failed: %s",
						mach_error_string (status));
			}
			thread_list = NULL;
			thread_list_len = 0;

			/* Only deallocate the task port, if it isn't our own.
			 * Don't know what would happen in that case, but this
			 * is what Apple's top does.. ;) */
			if (task_list[task] != port_task_self)
			{
				status = mach_port_deallocate (port_task_self,
						task_list[task]);
				if (status != KERN_SUCCESS)
					ERROR ("mach_port_deallocate failed: %s",
							mach_error_string (status));
			}

			if (ps != NULL)
				ps_list_add (task_name, &pse);
		} /* for (task_list) */

		if ((status = vm_deallocate (port_task_self,
				(vm_address_t) task_list,
				task_list_len * sizeof (task_t))) != KERN_SUCCESS)
		{
			ERROR ("vm_deallocate failed: %s",
					mach_error_string (status));
		}
		task_list = NULL;
		task_list_len = 0;

		if ((status = mach_port_deallocate (port_task_self, port_pset_priv))
				!= KERN_SUCCESS)
		{
			ERROR ("mach_port_deallocate failed: %s",
					mach_error_string (status));
		}
	} /* for (pset_list) */

	ps_submit_state ("running", running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies", zombies);
	ps_submit_state ("stopped", stopped);
	ps_submit_state ("blocked", blocked);

	for (ps = list_head_g; ps != NULL; ps = ps->next)
		ps_submit_proc_list (ps);
/* #endif HAVE_THREAD_INFO */

#elif KERNEL_LINUX
	int running  = 0;
	int sleeping = 0;
	int zombies  = 0;
	int stopped  = 0;
	int paging   = 0;
	int blocked  = 0;

	struct dirent *ent;
	DIR           *proc;
	int            pid;

	int        status;
	procstat_t ps;
	procstat_entry_t pse;
	char       state;

	procstat_t *ps_ptr;

	running = sleeping = zombies = stopped = paging = blocked = 0;
	ps_list_reset ();

	if ((proc = opendir ("/proc")) == NULL)
	{
		char errbuf[1024];
		ERROR ("Cannot open `/proc': %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while ((ent = readdir (proc)) != NULL)
	{
		if (!isdigit (ent->d_name[0]))
			continue;

		if ((pid = atoi (ent->d_name)) < 1)
			continue;

		status = ps_read_process (pid, &ps, &state);
		if (status != 0)
		{
			DEBUG ("ps_read_process failed: %i", status);
			continue;
		}

		pse.id       = pid;
		pse.age      = 0;

		pse.num_proc = ps.num_proc;
		pse.num_lwp  = ps.num_lwp;
		pse.vmem_rss = ps.vmem_rss;

		pse.vmem_minflt = 0;
		pse.vmem_minflt_counter = ps.vmem_minflt_counter;
		pse.vmem_majflt = 0;
		pse.vmem_majflt_counter = ps.vmem_majflt_counter;

		pse.cpu_user = 0;
		pse.cpu_user_counter = ps.cpu_user_counter;
		pse.cpu_system = 0;
		pse.cpu_system_counter = ps.cpu_system_counter;

		switch (state)
		{
			case 'R': running++;  break;
			case 'S': sleeping++; break;
			case 'D': blocked++;  break;
			case 'Z': zombies++;  break;
			case 'T': stopped++;  break;
			case 'W': paging++;   break;
		}

		ps_list_add (ps.name, &pse);
	}

	closedir (proc);

	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("paging",   paging);
	ps_submit_state ("blocked",  blocked);

	for (ps_ptr = list_head_g; ps_ptr != NULL; ps_ptr = ps_ptr->next)
		ps_submit_proc_list (ps_ptr);
#endif /* KERNEL_LINUX */

	return (0);
}