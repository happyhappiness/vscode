static void
dump_PortCfg(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
{
    while (s) {
        dump_generic_port(e, n, s);
        storeAppendPrintf(e, "\n");
        s = s->next;
    }
}