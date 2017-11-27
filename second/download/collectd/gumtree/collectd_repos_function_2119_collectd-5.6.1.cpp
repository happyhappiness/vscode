static int vmem_read (void)
{
#if KERNEL_LINUX
  derive_t pgpgin = 0;
  derive_t pgpgout = 0;
  int pgpgvalid = 0;

  derive_t pswpin = 0;
  derive_t pswpout = 0;
  int pswpvalid = 0;

  derive_t pgfault = 0;
  derive_t pgmajfault = 0;
  int pgfaultvalid = 0;

  FILE *fh;
  char buffer[1024];

  fh = fopen ("/proc/vmstat", "r");
  if (fh == NULL)
  {
    char errbuf[1024];
    ERROR ("vmem plugin: fopen (/proc/vmstat) failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  while (fgets (buffer, sizeof (buffer), fh) != NULL)
  {
    char *fields[4];
    int fields_num;
    char *key;
    char *endptr;
    derive_t counter;
    gauge_t gauge;

    fields_num = strsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));
    if (fields_num != 2)
      continue;

    key = fields[0];

    endptr = NULL;
    counter = strtoll (fields[1], &endptr, 10);
    if (fields[1] == endptr)
      continue;

    endptr = NULL;
    gauge = strtod (fields[1], &endptr);
    if (fields[1] == endptr)
      continue;

    /*
     * Number of pages
     *
     * The total number of {inst} pages, e. g dirty pages.
     */
    if (strncmp ("nr_", key, strlen ("nr_")) == 0)
    {
      char *inst = key + strlen ("nr_");
      if (strcmp(inst, "dirtied") == 0 || strcmp(inst, "written") == 0)
      {
        value_t value = { .derive = counter };
        submit_one (NULL, "vmpage_action", inst, value);
      }
      else
      {
        value_t value = { .gauge = gauge };
        submit_one (NULL, "vmpage_number", inst, value);
      }
    }

    /*
     * Page in and page outs. For memory and swap.
     */
    else if (strcmp ("pgpgin", key) == 0)
    {
      pgpgin = counter;
      pgpgvalid |= 0x01;
    }
    else if (strcmp ("pgpgout", key) == 0)
    {
      pgpgout = counter;
      pgpgvalid |= 0x02;
    }
    else if (strcmp ("pswpin", key) == 0)
    {
      pswpin = counter;
      pswpvalid |= 0x01;
    }
    else if (strcmp ("pswpout", key) == 0)
    {
      pswpout = counter;
      pswpvalid |= 0x02;
    }

    /*
     * Pagefaults
     */
    else if (strcmp ("pgfault", key) == 0)
    {
      pgfault = counter;
      pgfaultvalid |= 0x01;
    }
    else if (strcmp ("pgmajfault", key) == 0)
    {
      pgmajfault = counter;
      pgfaultvalid |= 0x02;
    }

    /*
     * Skip the other statistics if verbose output is disabled.
     */
    else if (verbose_output == 0)
      continue;

    /*
     * Number of page allocations, refills, steals and scans. This is collected
     * ``per zone'', i. e. for DMA, DMA32, normal and possibly highmem.
     */
    else if (strncmp ("pgalloc_", key, strlen ("pgalloc_")) == 0)
    {
      char *inst = key + strlen ("pgalloc_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "alloc", value);
    }
    else if (strncmp ("pgrefill_", key, strlen ("pgrefill_")) == 0)
    {
      char *inst = key + strlen ("pgrefill_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "refill", value);
    }
    else if (strncmp ("pgsteal_kswapd_", key, strlen ("pgsteal_kswapd_")) == 0)
    {
      char *inst = key + strlen ("pgsteal_kswapd_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "steal_kswapd", value);
    }
    else if (strncmp ("pgsteal_direct_", key, strlen ("pgsteal_direct_")) == 0)
    {
      char *inst = key + strlen ("pgsteal_direct_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "steal_direct", value);
    }
    /* For backwards compatibility (somewhen before 4.2.3) */
    else if (strncmp ("pgsteal_", key, strlen ("pgsteal_")) == 0)
    {
      char *inst = key + strlen ("pgsteal_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "steal", value);
    }
    else if (strncmp ("pgscan_kswapd_", key, strlen ("pgscan_kswapd_")) == 0)
    {
      char *inst = key + strlen ("pgscan_kswapd_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "scan_kswapd", value);
    }
    else if (strncmp ("pgscan_direct_", key, strlen ("pgscan_direct_")) == 0)
    {
      char *inst = key + strlen ("pgscan_direct_");
      value_t value  = { .derive = counter };
      submit_one (inst, "vmpage_action", "scan_direct", value);
    }

    /*
     * Page action
     *
     * number of pages moved to the active or inactive lists and freed, i. e.
     * removed from either list.
     */
    else if (strcmp ("pgfree", key) == 0)
    {
      value_t value  = { .derive = counter };
      submit_one (NULL, "vmpage_action", "free", value);
    }
    else if (strcmp ("pgactivate", key) == 0)
    {
      value_t value  = { .derive = counter };
      submit_one (NULL, "vmpage_action", "activate", value);
    }
    else if (strcmp ("pgdeactivate", key) == 0)
    {
      value_t value  = { .derive = counter };
      submit_one (NULL, "vmpage_action", "deactivate", value);
    }
  } /* while (fgets) */

  fclose (fh);
  fh = NULL;

  if (pgfaultvalid == 0x03)
    submit_two (NULL, "vmpage_faults", NULL, pgfault, pgmajfault);

  if (pgpgvalid == 0x03)
    submit_two (NULL, "vmpage_io", "memory", pgpgin, pgpgout);

  if (pswpvalid == 0x03)
    submit_two (NULL, "vmpage_io", "swap", pswpin, pswpout);
#endif /* KERNEL_LINUX */

  return (0);
}