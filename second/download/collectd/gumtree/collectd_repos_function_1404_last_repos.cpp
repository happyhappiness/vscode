static int swap_read_kstat(void) /* {{{ */
{
  gauge_t swap_alloc;
  gauge_t swap_resv;
  gauge_t swap_avail;

  struct anoninfo ai;

  if (swapctl(SC_AINFO, &ai) == -1) {
    char errbuf[1024];
    ERROR("swap plugin: swapctl failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
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
  swap_alloc = (gauge_t)((ai.ani_max - ai.ani_free) * pagesize);
  swap_resv = (gauge_t)((ai.ani_resv + ai.ani_free - ai.ani_max) * pagesize);
  swap_avail = (gauge_t)((ai.ani_max - ai.ani_resv) * pagesize);

  swap_submit_usage(NULL, swap_alloc, swap_avail, "reserved", swap_resv);
  return 0;
}