static void
dump_ecap_service_type(StoreEntry * entry, const char *name, const Adaptation::Ecap::Config &cfg)
{
    cfg.dumpService(entry, name);
}