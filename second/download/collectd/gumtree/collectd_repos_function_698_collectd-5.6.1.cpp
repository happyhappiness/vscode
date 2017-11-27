static int ps_read (void)
{
#if HAVE_THREAD_INFO
	kern_return_t            status;

	processor_set_t          port_pset_priv;

	task_array_t             task_list;
	mach_msg_type_number_t   task_list_len;

	int                      task_pid;
	char                     task_name[MAXCOMLEN + 1];

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
	for (mach_msg_type_number_t pset = 0; pset < pset_list_len; pset++)
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

		for (mach_msg_type_number_t task = 0; task < task_list_len; task++)
		{
			ps = NULL;
			if (mach_get_task_name (task_list[task],
						&task_pid,
						task_name, PROCSTAT_NAME_LEN) == 0)
			{
				/* search for at least one match */
				for (ps = list_head_g; ps != NULL; ps = ps->next)
					/* FIXME: cmdline should be here instead of NULL */
					if (ps_list_match (task_name, NULL, ps) == 1)
						break;
			}

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
				pse.vmem_size = task_basic_info.virtual_size;
				pse.vmem_rss = task_basic_info.resident_size;
				/* Does not seem to be easily exposed */
				pse.vmem_data = 0;
				pse.vmem_code = 0;

				pse.vmem_minflt_counter = task_events_info.cow_faults;
				pse.vmem_majflt_counter = task_events_info.faults;

				pse.cpu_user_counter = task_absolutetime_info.total_user;
				pse.cpu_system_counter = task_absolutetime_info.total_system;

				/* context switch counters not implemented */
				pse.cswitch_vol   = -1;
				pse.cswitch_invol = -1;
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

			for (mach_msg_type_number_t thread = 0; thread < thread_list_len; thread++)
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
				/* FIXME: cmdline should be here instead of NULL */
				ps_list_add (task_name, NULL, &pse);
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
	long           pid;

	char cmdline[CMDLINE_BUFFER_SIZE];

	int        status;
	procstat_t ps;
	procstat_entry_t pse;
	char       state;

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

		if ((pid = atol (ent->d_name)) < 1)
			continue;

		status = ps_read_process (pid, &ps, &state);
		if (status != 0)
		{
			DEBUG ("ps_read_process failed: %i", status);
			continue;
		}

		memset (&pse, 0, sizeof (pse));
		pse.id       = pid;
		pse.age      = 0;

		pse.num_proc   = ps.num_proc;
		pse.num_lwp    = ps.num_lwp;
		pse.vmem_size  = ps.vmem_size;
		pse.vmem_rss   = ps.vmem_rss;
		pse.vmem_data  = ps.vmem_data;
		pse.vmem_code  = ps.vmem_code;
		pse.stack_size = ps.stack_size;

		pse.vmem_minflt = 0;
		pse.vmem_minflt_counter = ps.vmem_minflt_counter;
		pse.vmem_majflt = 0;
		pse.vmem_majflt_counter = ps.vmem_majflt_counter;

		pse.cpu_user = 0;
		pse.cpu_user_counter = ps.cpu_user_counter;
		pse.cpu_system = 0;
		pse.cpu_system_counter = ps.cpu_system_counter;

		pse.io_rchar = ps.io_rchar;
		pse.io_wchar = ps.io_wchar;
		pse.io_syscr = ps.io_syscr;
		pse.io_syscw = ps.io_syscw;

		pse.cswitch_vol = ps.cswitch_vol;
		pse.cswitch_invol = ps.cswitch_invol;

		switch (state)
		{
			case 'R': running++;  break;
			case 'S': sleeping++; break;
			case 'D': blocked++;  break;
			case 'Z': zombies++;  break;
			case 'T': stopped++;  break;
			case 'W': paging++;   break;
		}

		ps_list_add (ps.name,
				ps_get_cmdline (pid, ps.name, cmdline, sizeof (cmdline)),
				&pse);
	}

	closedir (proc);

	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("paging",   paging);
	ps_submit_state ("blocked",  blocked);

	for (procstat_t *ps_ptr = list_head_g; ps_ptr != NULL; ps_ptr = ps_ptr->next)
		ps_submit_proc_list (ps_ptr);

	read_fork_rate();
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_FREEBSD
	int running  = 0;
	int sleeping = 0;
	int zombies  = 0;
	int stopped  = 0;
	int blocked  = 0;
	int idle     = 0;
	int wait     = 0;

	kvm_t *kd;
	char errbuf[_POSIX2_LINE_MAX];
	struct kinfo_proc *procs;          /* array of processes */
	struct kinfo_proc *proc_ptr = NULL;
	int count;                         /* returns number of processes */

	procstat_entry_t pse;

	ps_list_reset ();

	/* Open the kvm interface, get a descriptor */
	kd = kvm_openfiles (NULL, "/dev/null", NULL, 0, errbuf);
	if (kd == NULL)
	{
		ERROR ("processes plugin: Cannot open kvm interface: %s",
				errbuf);
		return (0);
	}

	/* Get the list of processes. */
	procs = kvm_getprocs(kd, KERN_PROC_ALL, 0, &count);
	if (procs == NULL)
	{
		ERROR ("processes plugin: Cannot get kvm processes list: %s",
				kvm_geterr(kd));
		kvm_close (kd);
		return (0);
	}

	/* Iterate through the processes in kinfo_proc */
	for (int i = 0; i < count; i++)
	{
		/* Create only one process list entry per _process_, i.e.
		 * filter out threads (duplicate PID entries). */
		if ((proc_ptr == NULL) || (proc_ptr->ki_pid != procs[i].ki_pid))
		{
			char cmdline[CMDLINE_BUFFER_SIZE] = "";
			_Bool have_cmdline = 0;

			proc_ptr = &(procs[i]);
			/* Don't probe system processes and processes without arguments */
			if (((procs[i].ki_flag & P_SYSTEM) == 0)
					&& (procs[i].ki_args != NULL))
			{
				char **argv;
				int argc;
				int status;

				/* retrieve the arguments */
				argv = kvm_getargv (kd, proc_ptr, /* nchr = */ 0);
				argc = 0;
				if ((argv != NULL) && (argv[0] != NULL))
				{
					while (argv[argc] != NULL)
						argc++;

					status = strjoin (cmdline, sizeof (cmdline), argv, argc, " ");
					if (status < 0)
						WARNING ("processes plugin: Command line did not fit into buffer.");
					else
						have_cmdline = 1;
				}
			} /* if (process has argument list) */

			pse.id       = procs[i].ki_pid;
			pse.age      = 0;

			pse.num_proc = 1;
			pse.num_lwp  = procs[i].ki_numthreads;

			pse.vmem_size = procs[i].ki_size;
			pse.vmem_rss = procs[i].ki_rssize * pagesize;
			pse.vmem_data = procs[i].ki_dsize * pagesize;
			pse.vmem_code = procs[i].ki_tsize * pagesize;
			pse.stack_size = procs[i].ki_ssize * pagesize;
			pse.vmem_minflt = 0;
			pse.vmem_minflt_counter = procs[i].ki_rusage.ru_minflt;
			pse.vmem_majflt = 0;
			pse.vmem_majflt_counter = procs[i].ki_rusage.ru_majflt;

			pse.cpu_user = 0;
			pse.cpu_system = 0;
			pse.cpu_user_counter = 0;
			pse.cpu_system_counter = 0;
			/*
			 * The u-area might be swapped out, and we can't get
			 * at it because we have a crashdump and no swap.
			 * If it's here fill in these fields, otherwise, just
			 * leave them 0.
			 */
			if (procs[i].ki_flag & P_INMEM)
			{
				pse.cpu_user_counter = procs[i].ki_rusage.ru_utime.tv_usec
				       	+ (1000000lu * procs[i].ki_rusage.ru_utime.tv_sec);
				pse.cpu_system_counter = procs[i].ki_rusage.ru_stime.tv_usec
					+ (1000000lu * procs[i].ki_rusage.ru_stime.tv_sec);
			}

			/* no I/O data */
			pse.io_rchar = -1;
			pse.io_wchar = -1;
			pse.io_syscr = -1;
			pse.io_syscw = -1;

			/* context switch counters not implemented */
			pse.cswitch_vol   = -1;
			pse.cswitch_invol = -1;

			ps_list_add (procs[i].ki_comm, have_cmdline ? cmdline : NULL, &pse);

			switch (procs[i].ki_stat)
			{
				case SSTOP:	stopped++;	break;
				case SSLEEP:	sleeping++;	break;
				case SRUN:	running++;	break;
				case SIDL:	idle++;		break;
				case SWAIT:	wait++;		break;
				case SLOCK:	blocked++;	break;
				case SZOMB:	zombies++;	break;
			}
		} /* if ((proc_ptr == NULL) || (proc_ptr->ki_pid != procs[i].ki_pid)) */
	}

	kvm_close(kd);

	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("blocked",  blocked);
	ps_submit_state ("idle",     idle);
	ps_submit_state ("wait",     wait);

	for (procstat_t *ps_ptr = list_head_g; ps_ptr != NULL; ps_ptr = ps_ptr->next)
		ps_submit_proc_list (ps_ptr);
/* #endif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_FREEBSD */

#elif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_OPENBSD
	int running  = 0;
	int sleeping = 0;
	int zombies  = 0;
	int stopped  = 0;
	int onproc   = 0;
	int idle     = 0;
	int dead     = 0;

	kvm_t *kd;
	char errbuf[1024];
	struct kinfo_proc *procs;          /* array of processes */
	struct kinfo_proc *proc_ptr = NULL;
	int count;                         /* returns number of processes */

	procstat_entry_t pse;

	ps_list_reset ();

	/* Open the kvm interface, get a descriptor */
	kd = kvm_open (NULL, NULL, NULL, 0, errbuf);
	if (kd == NULL)
	{
		ERROR ("processes plugin: Cannot open kvm interface: %s",
				errbuf);
		return (0);
	}

	/* Get the list of processes. */
	procs = kvm_getprocs(kd, KERN_PROC_ALL, 0, sizeof(struct kinfo_proc), &count);
	if (procs == NULL)
	{
		ERROR ("processes plugin: Cannot get kvm processes list: %s",
				kvm_geterr(kd));
		kvm_close (kd);
		return (0);
	}

	/* Iterate through the processes in kinfo_proc */
	for (int i = 0; i < count; i++)
	{
		/* Create only one process list entry per _process_, i.e.
		 * filter out threads (duplicate PID entries). */
		if ((proc_ptr == NULL) || (proc_ptr->p_pid != procs[i].p_pid))
		{
			char cmdline[CMDLINE_BUFFER_SIZE] = "";
			_Bool have_cmdline = 0;

			proc_ptr = &(procs[i]);
			/* Don't probe zombie processes  */
			if (!P_ZOMBIE(proc_ptr))
			{
				char **argv;
				int argc;
				int status;

				/* retrieve the arguments */
				argv = kvm_getargv (kd, proc_ptr, /* nchr = */ 0);
				argc = 0;
				if ((argv != NULL) && (argv[0] != NULL))
				{
					while (argv[argc] != NULL)
						argc++;

					status = strjoin (cmdline, sizeof (cmdline), argv, argc, " ");
					if (status < 0)
						WARNING ("processes plugin: Command line did not fit into buffer.");
					else
						have_cmdline = 1;
				}
			} /* if (process has argument list) */

			memset (&pse, 0, sizeof (pse));
			pse.id       = procs[i].p_pid;
			pse.age      = 0;

			pse.num_proc = 1;
			pse.num_lwp  = 1; /* XXX: accumulate p_tid values for a single p_pid ? */

			pse.vmem_rss = procs[i].p_vm_rssize * pagesize;
			pse.vmem_data = procs[i].p_vm_dsize * pagesize;
			pse.vmem_code = procs[i].p_vm_tsize * pagesize;
			pse.stack_size = procs[i].p_vm_ssize * pagesize;
			pse.vmem_size = pse.stack_size + pse.vmem_code + pse.vmem_data;
			pse.vmem_minflt = 0;
			pse.vmem_minflt_counter = procs[i].p_uru_minflt;
			pse.vmem_majflt = 0;
			pse.vmem_majflt_counter = procs[i].p_uru_majflt;

			pse.cpu_user = 0;
			pse.cpu_system = 0;
			pse.cpu_user_counter = procs[i].p_uutime_usec +
						(1000000lu * procs[i].p_uutime_sec);
			pse.cpu_system_counter = procs[i].p_ustime_usec +
						(1000000lu * procs[i].p_ustime_sec);

			/* no I/O data */
			pse.io_rchar = -1;
			pse.io_wchar = -1;
			pse.io_syscr = -1;
			pse.io_syscw = -1;

			/* context switch counters not implemented */
			pse.cswitch_vol   = -1;
			pse.cswitch_invol = -1;

			ps_list_add (procs[i].p_comm, have_cmdline ? cmdline : NULL, &pse);

			switch (procs[i].p_stat)
			{
				case SSTOP:	stopped++;	break;
				case SSLEEP:	sleeping++;	break;
				case SRUN:	running++;	break;
				case SIDL:	idle++;		break;
				case SONPROC:	onproc++;	break;
				case SDEAD:	dead++;		break;
				case SZOMB:	zombies++;	break;
			}
		} /* if ((proc_ptr == NULL) || (proc_ptr->p_pid != procs[i].p_pid)) */
	}

	kvm_close(kd);

	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("onproc",   onproc);
	ps_submit_state ("idle",     idle);
	ps_submit_state ("dead",     dead);

	for (procstat_t *ps_ptr = list_head_g; ps_ptr != NULL; ps_ptr = ps_ptr->next)
		ps_submit_proc_list (ps_ptr);
/* #endif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_OPENBSD */

#elif HAVE_PROCINFO_H
	/* AIX */
	int running  = 0;
	int sleeping = 0;
	int zombies  = 0;
	int stopped  = 0;
	int paging   = 0;
	int blocked  = 0;

	pid_t pindex = 0;
	int nprocs;

	procstat_entry_t pse;

	ps_list_reset ();
	while ((nprocs = getprocs64 (procentry, sizeof(struct procentry64),
					/* fdsinfo = */ NULL, sizeof(struct fdsinfo64),
					&pindex, MAXPROCENTRY)) > 0)
	{
		for (int i = 0; i < nprocs; i++)
		{
			tid64_t thindex;
			int nthreads;
			char arglist[MAXARGLN+1];
			char *cargs;
			char *cmdline;

			if (procentry[i].pi_state == SNONE) continue;
			/* if (procentry[i].pi_state == SZOMB)  FIXME */

			cmdline = procentry[i].pi_comm;
			cargs = procentry[i].pi_comm;
			if ( procentry[i].pi_flags & SKPROC )
			{
				if (procentry[i].pi_pid == 0)
					cmdline = "swapper";
				cargs = cmdline;
			}
			else
			{
				if (getargs(&procentry[i], sizeof(struct procentry64), arglist, MAXARGLN) >= 0)
				{
					int n;

					n = -1;
					while (++n < MAXARGLN)
					{
						if (arglist[n] == '\0')
						{
							if (arglist[n+1] == '\0')
								break;
							arglist[n] = ' ';
						}
					}
					cargs = arglist;
				}
			}

			pse.id       = procentry[i].pi_pid;
			pse.age      = 0;
			pse.num_lwp  = procentry[i].pi_thcount;
			pse.num_proc = 1;

			thindex=0;
			while ((nthreads = getthrds64(procentry[i].pi_pid,
							thrdentry, sizeof(struct thrdentry64),
							&thindex, MAXTHRDENTRY)) > 0)
			{
				int j;

				for (j=0; j< nthreads; j++)
				{
					switch (thrdentry[j].ti_state)
					{
						/* case TSNONE: break; */
						case TSIDL:	blocked++;	break; /* FIXME is really blocked */
						case TSRUN:	running++;	break;
						case TSSLEEP:	sleeping++;	break;
						case TSSWAP:	paging++;	break;
						case TSSTOP:	stopped++;	break;
						case TSZOMB:	zombies++;	break;
					}
				}
				if (nthreads < MAXTHRDENTRY)
					break;
			}

			pse.cpu_user = 0;
			/* tv_usec is nanosec ??? */
			pse.cpu_user_counter = procentry[i].pi_ru.ru_utime.tv_sec * 1000000 +
				procentry[i].pi_ru.ru_utime.tv_usec / 1000;

			pse.cpu_system = 0;
			/* tv_usec is nanosec ??? */
			pse.cpu_system_counter = procentry[i].pi_ru.ru_stime.tv_sec * 1000000 +
				procentry[i].pi_ru.ru_stime.tv_usec / 1000;

			pse.vmem_minflt = 0;
			pse.vmem_minflt_counter = procentry[i].pi_minflt;
			pse.vmem_majflt = 0;
			pse.vmem_majflt_counter = procentry[i].pi_majflt;

			pse.vmem_size = procentry[i].pi_tsize + procentry[i].pi_dvm * pagesize;
			pse.vmem_rss = (procentry[i].pi_drss + procentry[i].pi_trss) * pagesize;
			/* Not supported */
			pse.vmem_data = 0;
			pse.vmem_code = 0;
			pse.stack_size =  0;

			pse.io_rchar = -1;
			pse.io_wchar = -1;
			pse.io_syscr = -1;
			pse.io_syscw = -1;

			pse.cswitch_vol   = -1;
			pse.cswitch_invol = -1;

			ps_list_add (cmdline, cargs, &pse);
		} /* for (i = 0 .. nprocs) */

		if (nprocs < MAXPROCENTRY)
			break;
	} /* while (getprocs64() > 0) */
	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("paging",   paging);
	ps_submit_state ("blocked",  blocked);

	for (procstat_t *ps = list_head_g; ps != NULL; ps = ps->next)
		ps_submit_proc_list (ps);
/* #endif HAVE_PROCINFO_H */

#elif KERNEL_SOLARIS
	/*
	 * The Solaris section adds a few more process states and removes some
	 * process states compared to linux. Most notably there is no "PAGING"
	 * and "BLOCKED" state for a process.  The rest is similar to the linux
	 * code.
	 */
	int running = 0;
	int sleeping = 0;
	int zombies = 0;
	int stopped = 0;
	int detached = 0;
	int daemon = 0;
	int system = 0;
	int orphan = 0;

	struct dirent *ent;
	DIR *proc;

	int status;
	char state;

	char cmdline[PRARGSZ];

	ps_list_reset ();

	proc = opendir ("/proc");
	if (proc == NULL)
		return (-1);

	while ((ent = readdir(proc)) != NULL)
	{
		long pid;
		struct procstat ps;
		procstat_entry_t pse;
		char *endptr;

		if (!isdigit ((int) ent->d_name[0]))
			continue;

		pid = strtol (ent->d_name, &endptr, 10);
		if (*endptr != 0) /* value didn't completely parse as a number */
			continue;

		status = ps_read_process (pid, &ps, &state);
		if (status != 0)
		{
			DEBUG("ps_read_process failed: %i", status);
			continue;
		}

		memset (&pse, 0, sizeof (pse));
		pse.id = pid;
		pse.age = 0;

		pse.num_proc   = ps.num_proc;
		pse.num_lwp    = ps.num_lwp;
		pse.vmem_size  = ps.vmem_size;
		pse.vmem_rss   = ps.vmem_rss;
		pse.vmem_data  = ps.vmem_data;
		pse.vmem_code  = ps.vmem_code;
		pse.stack_size = ps.stack_size;

		pse.vmem_minflt = 0;
		pse.vmem_minflt_counter = ps.vmem_minflt_counter;
		pse.vmem_majflt = 0;
		pse.vmem_majflt_counter = ps.vmem_majflt_counter;

		pse.cpu_user = 0;
		pse.cpu_user_counter = ps.cpu_user_counter;
		pse.cpu_system = 0;
		pse.cpu_system_counter = ps.cpu_system_counter;

		pse.io_rchar = ps.io_rchar;
		pse.io_wchar = ps.io_wchar;
		pse.io_syscr = ps.io_syscr;
		pse.io_syscw = ps.io_syscw;

		pse.cswitch_vol = -1;
		pse.cswitch_invol = -1;

		switch (state)
		{
			case 'R': running++;  break;
			case 'S': sleeping++; break;
			case 'E': detached++; break;
			case 'Z': zombies++;  break;
			case 'T': stopped++;  break;
			case 'A': daemon++;   break;
			case 'Y': system++;   break;
			case 'O': orphan++;   break;
		}


		ps_list_add (ps.name,
				ps_get_cmdline (pid, ps.name, cmdline, sizeof (cmdline)),
				&pse);
	} /* while(readdir) */
	closedir (proc);

	ps_submit_state ("running",  running);
	ps_submit_state ("sleeping", sleeping);
	ps_submit_state ("zombies",  zombies);
	ps_submit_state ("stopped",  stopped);
	ps_submit_state ("detached", detached);
	ps_submit_state ("daemon",   daemon);
	ps_submit_state ("system",   system);
	ps_submit_state ("orphan",   orphan);

	for (procstat_t *ps_ptr = list_head_g; ps_ptr != NULL; ps_ptr = ps_ptr->next)
		ps_submit_proc_list (ps_ptr);

	read_fork_rate();
#endif /* KERNEL_SOLARIS */

	return (0);
}