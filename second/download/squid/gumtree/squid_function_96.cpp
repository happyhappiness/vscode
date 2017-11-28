static void
dump_http_header_replace(StoreEntry * entry, const char *name, header_mangler
                         header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        if (NULL == header[i].replacement)
            continue;

        storeAppendPrintf(entry, "%s %s %s\n", name, httpHeaderNameById(i),
                          header[i].replacement);
    }
}