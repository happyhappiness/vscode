void
fqdncache_restart(void)
{
    fqdncache_high = (long) (((float) Config.fqdncache.size *
                              (float) FQDN_HIGH_WATER) / (float) 100);
    fqdncache_low = (long) (((float) Config.fqdncache.size *
                             (float) FQDN_LOW_WATER) / (float) 100);
    purge_entries_fromhosts();
}