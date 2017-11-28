void
wordlistCat(const wordlist * w, MemBuf * mb)
{
    while (NULL != w) {
        mb->appendf("%s\n", w->key);
        w = w->next;
    }
}