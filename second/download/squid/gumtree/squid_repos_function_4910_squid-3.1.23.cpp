void
AuthNTLMConfig::dump(StoreEntry * entry, const char *name, AuthConfig * scheme)
{
    wordlist *list = authenticate;
    storeAppendPrintf(entry, "%s %s", name, "ntlm");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s ntlm children %d\n",
                      name, authenticateChildren);
    storeAppendPrintf(entry, "%s %s keep_alive %s\n", name, "ntlm", keep_alive ? "on" : "off");

}