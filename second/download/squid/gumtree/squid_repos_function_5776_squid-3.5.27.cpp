bool
Auth::Config::dump(StoreEntry *entry, const char *name, Auth::Config *scheme) const
{
    if (!authenticateProgram)
        return false; // not configured

    wordlist *list = authenticateProgram;
    storeAppendPrintf(entry, "%s %s", name, scheme->type());
    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }
    storeAppendPrintf(entry, "\n");

    storeAppendPrintf(entry, "%s %s realm " SQUIDSBUFPH "\n", name, scheme->type(), SQUIDSBUFPRINT(realm));

    storeAppendPrintf(entry, "%s %s children %d startup=%d idle=%d concurrency=%d\n",
                      name, scheme->type(),
                      authenticateChildren.n_max, authenticateChildren.n_startup,
                      authenticateChildren.n_idle, authenticateChildren.concurrency);

    if (keyExtrasLine.size() > 0)
        storeAppendPrintf(entry, "%s %s key_extras \"%s\"\n", name, scheme->type(), keyExtrasLine.termedBuf());

    return true;
}