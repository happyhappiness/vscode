static int swap_read(void) /* {{{ */
{
  struct swapent *swap_entries;
  int swap_num;
  int status;

  gauge_t used = 0;
  gauge_t total = 0;

  swap_num = swapctl(SWAP_NSWAP, NULL, 0);
  if (swap_num < 0) {
    ERROR("swap plugin: swapctl (SWAP_NSWAP) failed with status %i.", swap_num);
    return -1;
  } else if (swap_num == 0)
    return 0;

  swap_entries = calloc(swap_num, sizeof(*swap_entries));
  if (swap_entries == NULL) {
    ERROR("swap plugin: calloc failed.");
    return -1;
  }

  status = swapctl(SWAP_STATS, swap_entries, swap_num);
  if (status != swap_num) {
    ERROR("swap plugin: swapctl (SWAP_STATS) failed with status %i.", status);
    sfree(swap_entries);
    return -1;
  }

#if defined(DEV_BSIZE) && (DEV_BSIZE > 0)
#define C_SWAP_BLOCK_SIZE ((gauge_t)DEV_BSIZE)
#else
#define C_SWAP_BLOCK_SIZE 512.0
#endif

  /* TODO: Report per-device stats. The path name is available from
   * swap_entries[i].se_path */
  for (int i = 0; i < swap_num; i++) {
    if ((swap_entries[i].se_flags & SWF_ENABLE) == 0)
      continue;

    used += ((gauge_t)swap_entries[i].se_inuse) * C_SWAP_BLOCK_SIZE;
    total += ((gauge_t)swap_entries[i].se_nblks) * C_SWAP_BLOCK_SIZE;
  }

  if (total < used) {
    ERROR(
        "swap plugin: Total swap space (%g) is less than used swap space (%g).",
        total, used);
    sfree(swap_entries);
    return -1;
  }

  swap_submit_usage(NULL, used, total - used, NULL, NAN);

  sfree(swap_entries);
  return 0;
}