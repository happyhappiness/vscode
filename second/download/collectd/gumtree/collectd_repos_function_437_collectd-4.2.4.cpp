static int swap_read (void)
{
#if KERNEL_LINUX
	FILE *fh;
	char buffer[1024];
	
	char *fields[8];
	int numfields;

	unsigned long long swap_used   = 0LL;
	unsigned long long swap_cached = 0LL;
	unsigned long long swap_free   = 0LL;
	unsigned long long swap_total  = 0LL;

	if ((fh = fopen ("/proc/meminfo", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("memory: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, 1024, fh) != NULL)
	{
		unsigned long long *val = NULL;

		if (strncasecmp (buffer, "SwapTotal:", 10) == 0)
			val = &swap_total;
		else if (strncasecmp (buffer, "SwapFree:", 9) == 0)
			val = &swap_free;
		else if (strncasecmp (buffer, "SwapCached:", 11) == 0)
			val = &swap_cached;
		else
			continue;

		numfields = strsplit (buffer, fields, 8);

		if (numfields < 2)
			continue;

		*val = atoll (fields[1]) * 1024LL;
	}

	if (fclose (fh))
	{
		char errbuf[1024];
		WARNING ("memory: fclose: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	if ((swap_total == 0LL) || ((swap_free + swap_cached) > swap_total))
		return (-1);

	swap_used = swap_total - (swap_free + swap_cached);

	swap_submit ("used", swap_used);
	swap_submit ("free", swap_free);
	swap_submit ("cached", swap_cached);
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKSTAT
	unsigned long long swap_alloc;
	unsigned long long swap_resv;
	unsigned long long swap_avail;

	struct anoninfo ai;

	if (swapctl (SC_AINFO, &ai) == -1)
	{
		char errbuf[1024];
		ERROR ("swap plugin: swapctl failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	/*
	 * Calculations from:
	 * http://cvs.opensolaris.org/source/xref/on/usr/src/cmd/swap/swap.c
	 * Also see:
	 * http://www.itworld.com/Comp/2377/UIR980701perf/ (outdated?)
	 * /usr/include/vm/anon.h
	 *
	 * In short, swap -s shows: allocated + reserved = used, available
	 *
	 * However, Solaris does not allow to allocated/reserved more than the
	 * available swap (physical memory + disk swap), so the pedant may
	 * prefer: allocated + unallocated = reserved, available
	 * 
	 * We map the above to: used + resv = n/a, free
	 *
	 * Does your brain hurt yet?  - Christophe Kalt
	 *
	 * Oh, and in case you wonder,
	 * swap_alloc = pagesize * ( ai.ani_max - ai.ani_free );
	 * can suffer from a 32bit overflow.
	 */
	swap_alloc  = ai.ani_max - ai.ani_free;
	swap_alloc *= pagesize;
	swap_resv   = ai.ani_resv + ai.ani_free - ai.ani_max;
	swap_resv  *= pagesize;
	swap_avail  = ai.ani_max - ai.ani_resv;
	swap_avail *= pagesize;

	swap_submit ("used", swap_alloc);
	swap_submit ("free", swap_avail);
	swap_submit ("reserved", swap_resv - swap_alloc);
/* #endif HAVE_LIBKSTAT */

#elif defined(VM_SWAPUSAGE)
	int              mib[3];
	size_t           mib_len;
	struct xsw_usage sw_usage;
	size_t           sw_usage_len;

	mib_len = 2;
	mib[0]  = CTL_VM;
	mib[1]  = VM_SWAPUSAGE;

	sw_usage_len = sizeof (struct xsw_usage);

	if (sysctl (mib, mib_len, &sw_usage, &sw_usage_len, NULL, 0) != 0)
		return (-1);

	/* The returned values are bytes. */
	swap_submit ("used", sw_usage.xsu_used);
	swap_submit ("free", sw_usage.xsu_avail);
/* #endif VM_SWAPUSAGE */

#elif HAVE_LIBKVM
	struct kvm_swap data_s;
	int             status;

	unsigned long long used;
	unsigned long long free;
	unsigned long long total;

	if (kvm_obj == NULL)
		return (-1);

	/* only one structure => only get the grand total, no details */
	status = kvm_getswapinfo (kvm_obj, &data_s, 1, 0);
	if (status == -1)
		return (-1);

	total = (unsigned long long) data_s.ksw_total;
	used  = (unsigned long long) data_s.ksw_used;

	total *= (unsigned long long) kvm_pagesize;
	used  *= (unsigned long long) kvm_pagesize;

	free = total - used;

	swap_submit ("used", used);
	swap_submit ("free", free);
/* #endif HAVE_LIBKVM */

#elif HAVE_LIBSTATGRAB
	sg_swap_stats *swap;

	swap = sg_get_swap_stats ();

	if (swap == NULL)
		return (-1);

	swap_submit ("used", swap->used);
	swap_submit ("free", swap->free);
#endif /* HAVE_LIBSTATGRAB */

	return (0);
}