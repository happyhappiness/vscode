int ps_read_process (int pid, procstat_t *ps, char *state)
{
	char  filename[64];
	char  buffer[1024];
	FILE *fh;

	char *fields[64];
	char  fields_len;

	int  *tasks;
	int   i;

	int   ppid;
	int   name_len;

	long long unsigned cpu_user_counter;
	long long unsigned cpu_system_counter;
	long long unsigned vmem_rss;

	memset (ps, 0, sizeof (procstat_t));

	snprintf (filename, 64, "/proc/%i/stat", pid);
	filename[63] = '\0';

	if ((fh = fopen (filename, "r")) == NULL)
		return (-1);

	if (fgets (buffer, 1024, fh) == NULL)
	{
		fclose (fh);
		return (-1);
	}

	fclose (fh);

	fields_len = strsplit (buffer, fields, 64);
	if (fields_len < 24)
	{
		DEBUG ("processes plugin: ps_read_process (pid = %i):"
				" `%s' has only %i fields..",
				(int) pid, filename, fields_len);
		return (-1);
	}

	/* copy the name, strip brackets in the process */
	name_len = strlen (fields[1]) - 2;
	if ((fields[1][0] != '(') || (fields[1][name_len + 1] != ')'))
	{
		DEBUG ("No brackets found in process name: `%s'", fields[1]);
		return (-1);
	}
	fields[1] = fields[1] + 1;
	fields[1][name_len] = '\0';
	strncpy (ps->name, fields[1], PROCSTAT_NAME_LEN);

	ppid = atoi (fields[3]);

	*state = fields[2][0];

	if (*state == 'Z')
	{
		ps->num_lwp  = 0;
		ps->num_proc = 0;
	}
	else if ((tasks = ps_read_tasks (pid)) == NULL)
	{
		/* Kernel 2.4 or so */
		ps->num_lwp  = 1;
		ps->num_proc = 1;
	}
	else
	{
		ps->num_lwp  = 0;
		ps->num_proc = 1;
		for (i = 0; tasks[i] != 0; i++)
			ps->num_lwp++;

		free (tasks);
		tasks = NULL;
	}

	/* Leave the rest at zero if this is only a zombi */
	if (ps->num_proc == 0)
	{
		DEBUG ("This is only a zombi: pid = %i; name = %s;",
				pid, ps->name);
		return (0);
	}

	cpu_user_counter   = atoll (fields[13]);
	cpu_system_counter = atoll (fields[14]);
	vmem_rss = atoll (fields[23]);
	ps->vmem_minflt_counter = atol (fields[9]);
	ps->vmem_majflt_counter = atol (fields[11]);
	
	/* Convert jiffies to useconds */
	cpu_user_counter   = cpu_user_counter   * 1000000 / CONFIG_HZ;
	cpu_system_counter = cpu_system_counter * 1000000 / CONFIG_HZ;
	vmem_rss = vmem_rss * pagesize_g;

	ps->cpu_user_counter = (unsigned long) cpu_user_counter;
	ps->cpu_system_counter = (unsigned long) cpu_system_counter;
	ps->vmem_rss = (unsigned long) vmem_rss;

	/* success */
	return (0);
}