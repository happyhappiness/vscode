void
dump_acl_access(StoreEntry * entry, const char *name, acl_access * head)
{
    if (head) {
        wordlist *lines = head->treeDump(name, NULL);
        dump_wordlist(entry, lines);
        wordlistDestroy(&lines);
    }
}