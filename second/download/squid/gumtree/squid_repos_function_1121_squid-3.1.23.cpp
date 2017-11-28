static void
dump_wordlist(StoreEntry * entry, const char *name, wordlist * list)
{
    while (list != NULL) {
        storeAppendPrintf(entry, "%s %s\n", name, list->key);
        list = list->next;
    }
}