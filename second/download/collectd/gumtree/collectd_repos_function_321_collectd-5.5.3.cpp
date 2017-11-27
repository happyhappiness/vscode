static void check_ignorelist_and_submit32 (const char *dev,
    struct rtnl_link_stats *stats)
{
  struct ir_link_stats_storage_s s;

  COPY_RTNL_LINK_STATS(&s, stats);

  check_ignorelist_and_submit (dev, &s);
}