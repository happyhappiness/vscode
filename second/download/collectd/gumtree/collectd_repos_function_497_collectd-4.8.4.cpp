int ps_read_process (int pid, procstat_t *ps, char *state)
{
	char  filename[64];
	char  buffer[1024];

	char *fields[64];
	char  fields_len;

	int   i;

	int   ppid;
	int   name_len;

	long long unsigned cpu_user_counter;
	long long unsigned cpu_system_counter;
	long long unsigned vmem_size;
	long long unsigned vmem_rss;
	long long unsigned stack_size;

	memset (ps, 0, sizeof (procstat_t));

	ssnprintf (filename, sizeof (filename), "/proc/%i/stat", pid);

	i = read_file_contents (filename, buffer, sizeof(buffer) - 1);
	if (i <= 0)
		return (-1);
	buffer[i] = 0;

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
	else
	{
		if ( (ps->num_lwp = ps_read_tasks (pid)) == -1 )
		{
			/* returns -1 => kernel 2.4 */
			ps->num_lwp = 1;
		}
		ps->num_proc = 1;
	}

	/* Leave the rest at zero if this is only a zombi */
	if (ps->num_proc == 0)
	{
		DEBUG ("processes plugin: This is only a zombi: pid = %i; "
				"name = %s;", pid, ps->name);
		return (0);
	}

	cpu_user_counter   = atoll (fields[13]);
	cpu_system_counter = atoll (fields[14]);
	vmem_size          = atoll (fields[22]);
	vmem_rss           = atoll (fields[23]);
	ps->vmem_minflt_counter = atol (fields[9]);
	ps->vmem_majflt_counter = atol (fields[11]);

	{
		unsigned long long stack_start = atoll (fields[27]);
		unsigned long long stack_ptr   = atoll (fields[28]);

		stack_size = (stack_start > stack_ptr)
			? stack_start - stack_ptr
			: stack_ptr - stack_start;
	}

	/* Convert jiffies to useconds */
	cpu_user_counter   = cpu_user_counter   * 1000000 / CONFIG_HZ;
	cpu_system_counter = cpu_system_counter * 1000000 / CONFIG_HZ;
	vmem_rss = vmem_rss * pagesize_g;

	ps->cpu_user_counter = (unsigned long) cpu_user_counter;
	ps->cpu_system_counter = (unsigned long) cpu_system_counter;
	ps->vmem_size = (unsigned long) vmem_size;
	ps->vmem_rss = (unsigned long) vmem_rss;
	ps->stack_size = (unsigned long) stack_size;

	/* success */
	return (0);
}