void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    wordlist *values = head->dump();
    dump_wordlist(entry, values);
    wordlistDestroy(&values);
}