static void
dump_YesNoNone(StoreEntry * entry, const char *name, YesNoNone &option)
{
    if (option.configured())
        dump_onoff(entry, name, option ? 1 : 0);
}