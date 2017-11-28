static void
compileUnoptimisedREs(RegexList **curlist, wordlist * wl)
{
    RegexList **Tail;
    RegexList **newTail;
    int flags = REG_EXTENDED | REG_NOSUB;

    for (Tail = curlist; *Tail != NULL; Tail = &((*Tail)->next))
        ;

    while (wl != NULL) {
        if (strcmp(wl->key, "-i") == 0) {
            flags |= REG_ICASE;
        } else if (strcmp(wl->key, "+i") == 0) {
            flags &= ~REG_ICASE;
        } else {
            newTail = compileRE( Tail, wl->key , flags );
            if (newTail == NULL)
                debugs(28, DBG_CRITICAL, "ERROR: Skipping regular expression. Compile failed: '" << wl->key << "'");
            else
                Tail = newTail;
        }
        wl = wl->next;
    }
}