static void
dump_icap_service_type(StoreEntry * entry, const char *name, const Adaptation::Icap::Config &cfg)
{
    cfg.dumpService(entry, name);
}