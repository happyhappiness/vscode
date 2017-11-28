void
AuthNegotiateConfig::dump(StoreEntry * entry, const char *name, AuthConfig * scheme)
{
    wordlist *list = authenticate;
    storeAppendPrintf(entry, "%s %s", name, "negotiate");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s negotiate children %d\n",
                      name, authenticateChildren);
    storeAppendPrintf(entry, "%s %s keep_alive %s\n", name, "negotiate", keep_alive ? "on" : "off");

}