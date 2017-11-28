void
wordlistDestroy(wordlist ** list)
{
    while (*list != nullptr) {
        const char *k = wordlistChopHead(list);
        safe_free(k);
    }
}