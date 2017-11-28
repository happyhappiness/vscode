static void dump_icap_service_failure_limit(StoreEntry *entry, const char *name, const Adaptation::Icap::Config &cfg)
{
    storeAppendPrintf(entry, "%s %d", name, cfg.service_failure_limit);
    if (cfg.oldest_service_failure > 0) {
        storeAppendPrintf(entry, " in %d seconds", (int)cfg.oldest_service_failure);
    }
    storeAppendPrintf(entry, "\n");
}