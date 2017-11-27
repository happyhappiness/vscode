static int swap_read (void)
{
#if KERNEL_LINUX
	FILE *fh;
	char buffer[1024];
	
	char *fields[8];
	int numfields;

	derive_t swap_used   = 0;
	derive_t swap_cached = 0;
	derive_t swap_free   = 0;
	derive_t swap_total  = 0;
	derive_t swap_in     = 0;
	derive_t swap_out    = 0;

	if ((fh = fopen ("/proc/meminfo", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("memory: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, 1024, fh) != NULL)
	{
		derive_t *val = NULL;

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

		*val = (derive_t) atoll (fields[1]) * 1024LL;
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

	if ((fh = fopen ("/proc/vmstat", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("swap: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, 1024, fh) != NULL)
	{
		derive_t *val = NULL;

		if (strncasecmp (buffer, "pswpin", 6) == 0)
			val = &swap_in;
		else if (strncasecmp (buffer, "pswpout", 7) == 0)
			val = &swap_out;
		else
			continue;

		numfields = strsplit (buffer, fields, 8);

		if (numfields < 2)
			continue;

		*val = (derive_t) atoll (fields[1]);
	}

	if (fclose (fh))
	{
		char errbuf[1024];
		WARNING ("swap: fclose: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	swap_submit ("used", swap_used, DS_TYPE_GAUGE);
	swap_submit ("free", swap_free, DS_TYPE_GAUGE);
	swap_submit ("cached", swap_cached, DS_TYPE_GAUGE);
	swap_submit ("in", swap_in, DS_TYPE_DERIVE);
	swap_submit ("out", swap_out, DS_TYPE_DERIVE);

/* #endif KERNEL_LINUX */

#elif HAVE_LIBKSTAT
	derive_t swap_alloc;
	derive_t swap_resv;
	derive_t swap_avail;

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
	swap_alloc  = (derive_t) ((ai.ani_max - ai.ani_free) * pagesize);
	swap_resv   = (derive_t) ((ai.ani_resv + ai.ani_free - ai.ani_max)
			* pagesize);
	swap_avail  = (derive_t) ((ai.ani_max - ai.ani_resv) * pagesize);

	swap_submit ("used", swap_alloc, DS_TYPE_GAUGE);
	swap_submit ("free", swap_avail, DS_TYPE_GAUGE);
	swap_submit ("reserved", swap_resv, DS_TYPE_GAUGE);
/* #endif HAVE_LIBKSTAT */

#elif HAVE_SWAPCTL
	struct swapent *swap_entries;
	int swap_num;
	int status;
	int i;

	derive_t used  = 0;
	derive_t total = 0;

	/*
	 * XXX: This is the syntax for the *BSD `swapctl', which has the
	 * following prototype:
	 *   swapctl (int cmd, void *arg, int misc);
	 *
	 * HP-UX and Solaris (and possibly other UNIXes) provide `swapctl',
	 * too, but with the following prototype:
	 *   swapctl (int cmd, void *arg);
	 *
	 * Solaris is usually handled in the KSTAT case above. For other UNIXes
	 * a separate case for the other version of `swapctl' may be necessary.
	 */
	swap_num = swapctl (SWAP_NSWAP, NULL, 0);
	if (swap_num < 0)
	{
		ERROR ("swap plugin: swapctl (SWAP_NSWAP) failed with status %i.",
				swap_num);
		return (-1);
	}
	else if (swap_num == 0)
		return (0);

	swap_entries = calloc (swap_num, sizeof (*swap_entries));
	if (swap_entries == NULL)
	{
		ERROR ("swap plugin: calloc failed.");
		return (-1);
	}

	status = swapctl (SWAP_STATS, swap_entries, swap_num);
	if (status != swap_num)
	{
		ERROR ("swap plugin: swapctl (SWAP_STATS) failed with status %i.",
				status);
		sfree (swap_entries);
		return (-1);
	}

#if defined(DEV_BSIZE) && (DEV_BSIZE > 0)
# define C_SWAP_BLOCK_SIZE ((derive_t) DEV_BSIZE)
#else
# define C_SWAP_BLOCK_SIZE ((derive_t) 512)
#endif

	for (i = 0; i < swap_num; i++)
	{
		if ((swap_entries[i].se_flags & SWF_ENABLE) == 0)
			continue;

		used  += ((derive_t) swap_entries[i].se_inuse)
			* C_SWAP_BLOCK_SIZE;
		total += ((derive_t) swap_entries[i].se_nblks)
			* C_SWAP_BLOCK_SIZE;
	}

	if (total < used)
	{
		ERROR ("swap plugin: Total swap space (%"PRIu64") "
				"is less than used swap space (%"PRIu64").",
				total, used);
		return (-1);
	}

	swap_submit ("used", used, DS_TYPE_GAUGE);
	swap_submit ("free", total - used, DS_TYPE_GAUGE);

	sfree (swap_entries);
/* #endif HAVE_SWAPCTL */

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
	swap_submit ("used", (derive_t) sw_usage.xsu_used, DS_TYPE_GAUGE);
	swap_submit ("free", (derive_t) sw_usage.xsu_avail, DS_TYPE_GAUGE);
/* #endif VM_SWAPUSAGE */

#elif HAVE_LIBKVM_GETSWAPINFO
	struct kvm_swap data_s;
	int             status;

	derive_t used;
	derive_t free;
	derive_t total;

	if (kvm_obj == NULL)
		return (-1);

	/* only one structure => only get the grand total, no details */
	status = kvm_getswapinfo (kvm_obj, &data_s, 1, 0);
	if (status == -1)
		return (-1);

	total = (derive_t) data_s.ksw_total;
	used  = (derive_t) data_s.ksw_used;

	total *= (derive_t) kvm_pagesize;
	used  *= (derive_t) kvm_pagesize;

	free = total - used;

	swap_submit ("used", used, DS_TYPE_GAUGE);
	swap_submit ("free", free, DS_TYPE_GAUGE);
/* #endif HAVE_LIBKVM_GETSWAPINFO */

#elif HAVE_LIBSTATGRAB
	sg_swap_stats *swap;

	swap = sg_get_swap_stats ();

	if (swap == NULL)
		return (-1);

	swap_submit ("used", (derive_t) swap->used, DS_TYPE_GAUGE);
	swap_submit ("free", (derive_t) swap->free, DS_TYPE_GAUGE);
#endif /* HAVE_LIBSTATGRAB */

	return (0);
}