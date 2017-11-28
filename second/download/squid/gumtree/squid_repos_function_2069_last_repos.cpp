char *
wordlistChopHead(wordlist **wl)
{
    if (*wl == nullptr)
        return nullptr;

    wordlist *w = *wl;
    char *rv = w->key;
    *wl = w->next;
    delete w;
    return rv;
}