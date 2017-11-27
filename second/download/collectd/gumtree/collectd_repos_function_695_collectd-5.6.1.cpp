static int ps_read_process(long pid, procstat_t *ps, char *state)
{
	char filename[64];
	char f_psinfo[64], f_usage[64];
	char *buffer;

	pstatus_t *myStatus;
	psinfo_t *myInfo;
	prusage_t *myUsage;

	snprintf(filename, sizeof (filename), "/proc/%li/status", pid);
	snprintf(f_psinfo, sizeof (f_psinfo), "/proc/%li/psinfo", pid);
	snprintf(f_usage, sizeof (f_usage), "/proc/%li/usage", pid);


	buffer = calloc(1, sizeof (pstatus_t));
	read_file_contents(filename, buffer, sizeof (pstatus_t));
	myStatus = (pstatus_t *) buffer;

	buffer = calloc(1, sizeof (psinfo_t));
	read_file_contents(f_psinfo, buffer, sizeof (psinfo_t));
	myInfo = (psinfo_t *) buffer;

	buffer = calloc(1, sizeof (prusage_t));
	read_file_contents(f_usage, buffer, sizeof (prusage_t));
	myUsage = (prusage_t *) buffer;

	sstrncpy(ps->name, myInfo->pr_fname, sizeof (myInfo->pr_fname));
	ps->num_lwp = myStatus->pr_nlwp;
	if (myInfo->pr_wstat != 0) {
		ps->num_proc = 0;
		ps->num_lwp = 0;
		*state = (char) 'Z';

		sfree(myStatus);
		sfree(myInfo);
		sfree(myUsage);
		return (0);
	} else {
		ps->num_proc = 1;
		ps->num_lwp = myInfo->pr_nlwp;
	}

	/*
	 * Convert system time and user time from nanoseconds to microseconds
	 * for compatibility with the linux module
	 */
	ps->cpu_system_counter = myStatus -> pr_stime.tv_nsec / 1000;
	ps->cpu_user_counter = myStatus -> pr_utime.tv_nsec / 1000;

	/*
	 * Convert rssize from KB to bytes to be consistent w/ the linux module
	 */
	ps->vmem_rss = myInfo->pr_rssize * 1024;
	ps->vmem_size = myInfo->pr_size * 1024;
	ps->vmem_minflt_counter = myUsage->pr_minf;
	ps->vmem_majflt_counter = myUsage->pr_majf;

	/*
	 * TODO: Data and code segment calculations for Solaris
	 */

	ps->vmem_data = -1;
	ps->vmem_code = -1;
	ps->stack_size = myStatus->pr_stksize;

	/*
	 * Calculating input/ouput chars
	 * Formula used is total chars / total blocks => chars/block
	 * then convert input/output blocks to chars
	 */
	ulong_t tot_chars = myUsage->pr_ioch;
	ulong_t tot_blocks = myUsage->pr_inblk + myUsage->pr_oublk;
	ulong_t chars_per_block = 1;
	if (tot_blocks != 0)
		chars_per_block = tot_chars / tot_blocks;
	ps->io_rchar = myUsage->pr_inblk * chars_per_block;
	ps->io_wchar = myUsage->pr_oublk * chars_per_block;
	ps->io_syscr = myUsage->pr_sysc;
	ps->io_syscw = myUsage->pr_sysc;

	/*
	 * TODO: context switch counters for Solaris
   */
	ps->cswitch_vol   = -1;
	ps->cswitch_invol = -1;


	/*
	 * TODO: Find way of setting BLOCKED and PAGING status
	 */

	*state = (char) 'R';
	if (myStatus->pr_flags & PR_ASLEEP)
		*state = (char) 'S';
	else if (myStatus->pr_flags & PR_STOPPED)
		*state = (char) 'T';
	else if (myStatus->pr_flags & PR_DETACH)
		*state = (char) 'E';
	else if (myStatus->pr_flags & PR_DAEMON)
		*state = (char) 'A';
	else if (myStatus->pr_flags & PR_ISSYS)
		*state = (char) 'Y';
	else if (myStatus->pr_flags & PR_ORPHAN)
		*state = (char) 'O';

	sfree(myStatus);
	sfree(myInfo);
	sfree(myUsage);

	return (0);
}