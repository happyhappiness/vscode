static void
dump_wordlist(StoreEntry * entry, wordlist *words)
{
    for (wordlist *word = words; word; word = word->next)
        // XXX: use something like ConfigParser::QuoteString() here
        storeAppendPrintf(entry, "%s ", word->key);
}