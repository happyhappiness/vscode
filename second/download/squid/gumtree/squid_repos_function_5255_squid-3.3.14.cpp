void
Auth::Ntlm::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme)
{
    wordlist *list = authenticateProgram;
    storeAppendPrintf(entry, "%s %s", name, "ntlm");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s ntlm children %d startup=%d idle=%d concurrency=%d\n",
                      name, authenticateChildren.n_max, authenticateChildren.n_startup, authenticateChildren.n_idle, authenticateChildren.concurrency);
    storeAppendPrintf(entry, "%s %s keep_alive %s\n", name, "ntlm", keep_alive ? "on" : "off");

}