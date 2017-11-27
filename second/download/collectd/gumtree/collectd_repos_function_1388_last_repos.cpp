static int za_read(void) {
  gauge_t arc_hits, arc_misses, l2_hits, l2_misses;
  kstat_t *ksp = NULL;

#if defined(KERNEL_LINUX)
  FILE *fh;
  char buffer[1024];

  fh = fopen(ZOL_ARCSTATS_FILE, "r");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("zfs_arc plugin: Opening \"%s\" failed: %s", ZOL_ARCSTATS_FILE,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  /* Ignore the first two lines because they contain information about the rest
   * of the file.
   * See kstat_seq_show_headers module/spl/spl-kstat.c of the spl kernel module.
   */
  if ((fgets(buffer, sizeof(buffer), fh) == NULL) ||
      (fgets(buffer, sizeof(buffer), fh) == NULL)) {
    ERROR("zfs_arc plugin: \"%s\" does not contain at least two lines.",
          ZOL_ARCSTATS_FILE);
    fclose(fh);
    return -1;
  }

  ksp = llist_create();
  if (ksp == NULL) {
    ERROR("zfs_arc plugin: `llist_create' failed.");
    fclose(fh);
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[3];
    value_t v;
    int status;

    status = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (status != 3)
      continue;

    status = parse_value(fields[2], &v, DS_TYPE_DERIVE);
    if (status != 0)
      continue;

    put_zfs_value(ksp, fields[0], v);
  }

  fclose(fh);

#elif defined(KERNEL_SOLARIS)
  get_kstat(&ksp, "zfs", 0, "arcstats");
  if (ksp == NULL) {
    ERROR("zfs_arc plugin: Cannot find zfs:0:arcstats kstat.");
    return -1;
  }
#endif

  /* Sizes */
  za_read_gauge(ksp, "anon_size", "cache_size", "anon_size");
  za_read_gauge(ksp, "c", "cache_size", "c");
  za_read_gauge(ksp, "c_max", "cache_size", "c_max");
  za_read_gauge(ksp, "c_min", "cache_size", "c_min");
  za_read_gauge(ksp, "hdr_size", "cache_size", "hdr_size");
  za_read_gauge(ksp, "metadata_size", "cache_size", "metadata_size");
  za_read_gauge(ksp, "mfu_ghost_size", "cache_size", "mfu_ghost_size");
  za_read_gauge(ksp, "mfu_size", "cache_size", "mfu_size");
  za_read_gauge(ksp, "mru_ghost_size", "cache_size", "mru_ghost_size");
  za_read_gauge(ksp, "mru_size", "cache_size", "mru_size");
  za_read_gauge(ksp, "other_size", "cache_size", "other_size");
  za_read_gauge(ksp, "p", "cache_size", "p");
  za_read_gauge(ksp, "size", "cache_size", "arc");

  /* The "l2_size" value has disappeared from Solaris some time in
   * early 2013, and has only reappeared recently in Solaris 11.2.
   * Stop trying if we ever fail to read it, so we don't spam the log.
   */
  static int l2_size_avail = 1;
  if (l2_size_avail && za_read_gauge(ksp, "l2_size", "cache_size", "L2") != 0)
    l2_size_avail = 0;

  /* Operations */
  za_read_derive(ksp, "deleted", "cache_operation", "deleted");
#if defined(KERNEL_FREEBSD)
  za_read_derive(ksp, "allocated", "cache_operation", "allocated");
#endif

  /* Issue indicators */
  za_read_derive(ksp, "mutex_miss", "mutex_operations", "miss");
  za_read_derive(ksp, "hash_collisions", "hash_collisions", "");
  za_read_derive(ksp, "memory_throttle_count", "memory_throttle_count", "");

  /* Evictions */
  za_read_derive(ksp, "evict_l2_cached", "cache_eviction", "cached");
  za_read_derive(ksp, "evict_l2_eligible", "cache_eviction", "eligible");
  za_read_derive(ksp, "evict_l2_ineligible", "cache_eviction", "ineligible");

  /* Hits / misses */
  za_read_derive(ksp, "demand_data_hits", "cache_result", "demand_data-hit");
  za_read_derive(ksp, "demand_metadata_hits", "cache_result",
                 "demand_metadata-hit");
  za_read_derive(ksp, "prefetch_data_hits", "cache_result",
                 "prefetch_data-hit");
  za_read_derive(ksp, "prefetch_metadata_hits", "cache_result",
                 "prefetch_metadata-hit");
  za_read_derive(ksp, "demand_data_misses", "cache_result", "demand_data-miss");
  za_read_derive(ksp, "demand_metadata_misses", "cache_result",
                 "demand_metadata-miss");
  za_read_derive(ksp, "prefetch_data_misses", "cache_result",
                 "prefetch_data-miss");
  za_read_derive(ksp, "prefetch_metadata_misses", "cache_result",
                 "prefetch_metadata-miss");
  za_read_derive(ksp, "mfu_hits", "cache_result", "mfu-hit");
  za_read_derive(ksp, "mfu_ghost_hits", "cache_result", "mfu_ghost-hit");
  za_read_derive(ksp, "mru_hits", "cache_result", "mru-hit");
  za_read_derive(ksp, "mru_ghost_hits", "cache_result", "mru_ghost-hit");

  cdtime_t now = cdtime();

  /* Ratios */
  if ((value_to_rate(&arc_hits, (value_t){.derive = get_zfs_value(ksp, "hits")},
                     DS_TYPE_DERIVE, now, &arc_hits_state) == 0