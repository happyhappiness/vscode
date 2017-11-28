
    dump_stat = hs;
    storeAppendPrintf(e, "\nHeader Stats: %s\n", hs->label);
    storeAppendPrintf(e, "\nField type distribution\n");
    storeAppendPrintf(e, "%2s\t %-20s\t %5s\t %6s\n",
                      "id", "name", "count", "#/header");
    statHistDump(&hs->fieldTypeDistr, e, httpHeaderFieldStatDumper);
    storeAppendPrintf(e, "\nCache-control directives distribution\n");
    storeAppendPrintf(e, "%2s\t %-20s\t %5s\t %6s\n",
                      "id", "name", "count", "#/cc_field");
    statHistDump(&hs->ccTypeDistr, e, httpHdrCcStatDumper);
    storeAppendPrintf(e, "\nSurrogate-control directives distribution\n");
    storeAppendPrintf(e, "%2s\t %-20s\t %5s\t %6s\n",
                      "id", "name", "count", "#/sc_field");
    statHistDump(&hs->scTypeDistr, e, httpHdrScStatDumper);
    storeAppendPrintf(e, "\nNumber of fields per header distribution\n");
    storeAppendPrintf(e, "%2s\t %-5s\t %5s\t %6s\n",
                      "id", "#flds", "count", "%total");
    statHistDump(&hs->hdrUCountDistr, e, httpHeaderFldsPerHdrDumper);
    dump_stat = NULL;
}

void
httpHeaderStoreReport(StoreEntry * e)
{
