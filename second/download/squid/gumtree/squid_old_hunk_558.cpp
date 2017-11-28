    }

    return true;
}

void
Format::Format::dump(StoreEntry * entry, const char *name)
{
    debugs(46, 4, HERE);

    // loop rather than recursing to conserve stack space.
    for (Format *format = this; format; format = format->next) {
        debugs(46, 3, HERE << "Dumping format definition for " << format->name);
        storeAppendPrintf(entry, "format %s ", format->name);

        for (Token *t = format->format; t; t = t->next) {
            if (t->type == LFT_STRING)
                storeAppendPrintf(entry, "%s", t->data.string);
            else {
                char argbuf[256];
                char *arg = NULL;
                ByteCode_t type = t->type;
