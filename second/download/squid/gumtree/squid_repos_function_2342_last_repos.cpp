void
dump_wccp2_method(StoreEntry * e, const char *label, int v)
{
    switch (v) {
    case WCCP2_METHOD_GRE:
        storeAppendPrintf(e, "%s gre\n", label);
        break;
    case WCCP2_METHOD_L2:
        storeAppendPrintf(e, "%s l2\n", label);
        break;
    default:
        debugs(80, DBG_CRITICAL, "FATAL: WCCPv2 configured method (" << v << ") is not valid.");
        self_destruct();
    }
}