static void
dump_PortCfg(StoreEntry * e, const char *n, const AnyP::PortCfgPointer &s)
{
    for (AnyP::PortCfgPointer p = s; p != NULL; p = p->next) {
        dump_generic_port(e, n, p);
        storeAppendPrintf(e, "\n");
    }
}