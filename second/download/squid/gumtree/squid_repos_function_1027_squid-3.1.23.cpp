static void
dump_acl(StoreEntry * entry, const char *name, ACL * ae)
{
    wordlist *w;
    wordlist *v;

    while (ae != NULL) {
        debugs(3, 3, "dump_acl: " << name << " " << ae->name);
        storeAppendPrintf(entry, "%s %s %s ",
                          name,
                          ae->name,
                          ae->typeString());
        v = w = ae->dump();

        while (v != NULL) {
            debugs(3, 3, "dump_acl: " << name << " " << ae->name << " " << v->key);
            storeAppendPrintf(entry, "%s ", v->key);
            v = v->next;
        }

        storeAppendPrintf(entry, "\n");
        wordlistDestroy(&w);
        ae = ae->next;
    }
}