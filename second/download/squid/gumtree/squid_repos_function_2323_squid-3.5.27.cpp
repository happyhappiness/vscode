void
Notes::dump(StoreEntry *entry, const char *key)
{
    typedef Notes::NotesList::iterator AMLI;
    for (AMLI m = notes.begin(); m != notes.end(); ++m) {
        typedef Note::Values::iterator VLI;
        for (VLI v =(*m)->values.begin(); v != (*m)->values.end(); ++v ) {
            storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s",
                              key, SQUIDSTRINGPRINT((*m)->key), ConfigParser::QuoteString((*v)->value));
            dump_acl_list(entry, (*v)->aclList);
            storeAppendPrintf(entry, "\n");
        }
    }
}