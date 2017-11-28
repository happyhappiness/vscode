static void
dump_authparam(StoreEntry * entry, const char *name, Auth::ConfigVector cfg)
{
    for (Auth::ConfigVector::iterator  i = cfg.begin(); i != cfg.end(); ++i)
        (*i)->dump(entry, name, (*i));
}