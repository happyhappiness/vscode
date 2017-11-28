static void
dump_authparam(StoreEntry * entry, const char *name, authConfig cfg)
{
    for (authConfig::iterator  i = cfg.begin(); i != cfg.end(); ++i)
        (*i)->dump(entry, name, (*i));
}