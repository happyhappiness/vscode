static int get_memory_stats(virDomainPtr domain) {
  virDomainMemoryStatPtr minfo =
      calloc(VIR_DOMAIN_MEMORY_STAT_NR, sizeof(virDomainMemoryStatStruct));
  if (minfo == NULL) {
    ERROR("virt plugin: malloc failed.");
    return -1;
  }

  int mem_stats =
      virDomainMemoryStats(domain, minfo, VIR_DOMAIN_MEMORY_STAT_NR, 0);
  if (mem_stats < 0) {
    ERROR("virt plugin: virDomainMemoryStats failed with mem_stats %i.",
          mem_stats);
    sfree(minfo);
    return mem_stats;
  }

  for (int i = 0; i < mem_stats; i++)
    memory_stats_submit((gauge_t)minfo[i].val * 1024, domain, minfo[i].tag);

  sfree(minfo);
  return 0;
}