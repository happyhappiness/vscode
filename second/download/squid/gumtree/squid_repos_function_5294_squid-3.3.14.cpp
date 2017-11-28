void
Auth::Digest::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme)
{
    wordlist *list = authenticateProgram;
    debugs(29, 9, "authDigestCfgDump: Dumping configuration");
    storeAppendPrintf(entry, "%s %s", name, "digest");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s %s realm %s\n%s %s children %d startup=%d idle=%d concurrency=%d\n%s %s nonce_max_count %d\n%s %s nonce_max_duration %d seconds\n%s %s nonce_garbage_interval %d seconds\n",
                      name, "digest", digestAuthRealm,
                      name, "digest", authenticateChildren.n_max, authenticateChildren.n_startup, authenticateChildren.n_idle, authenticateChildren.concurrency,
                      name, "digest", noncemaxuses,
                      name, "digest", (int) noncemaxduration,
                      name, "digest", (int) nonceGCInterval);
}