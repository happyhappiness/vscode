void
Adaptation::Config::DumpMetaHeader(StoreEntry *entry, const char *name)
{
    typedef MetaHeaders::iterator AMLI;
    for (AMLI m = metaHeaders.begin(); m != metaHeaders.end(); ++m) {
        typedef MetaHeader::Values::iterator VLI;
        for (VLI v =(*m)->values.begin(); v != (*m)->values.end(); ++v ) {
            storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s",
                              name, SQUIDSTRINGPRINT((*m)->name), ConfigParser::QuoteString((*v)->value));
            dump_acl_list(entry, (*v)->aclList);
            storeAppendPrintf(entry, "\n");
        }
    }
}