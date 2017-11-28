void
dump_wccp2_amethod(StoreEntry * e, const char *label, int v)
{
    switch (v) {
    case WCCP2_ASSIGNMENT_METHOD_HASH:
        storeAppendPrintf(e, "%s hash\n", label);
        break;
    case WCCP2_ASSIGNMENT_METHOD_MASK:
        storeAppendPrintf(e, "%s mask\n", label);
        break;
    default:
        debugs(80, DBG_CRITICAL, "FATAL: WCCPv2 configured " << label << " (" << v << ") is not valid.");
        self_destruct();
    }
}