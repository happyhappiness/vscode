static void
dump_client_delay_pool_count(StoreEntry * entry, const char *name, ClientDelayConfig &cfg)
{
    cfg.dumpPoolCount (entry, name);
}