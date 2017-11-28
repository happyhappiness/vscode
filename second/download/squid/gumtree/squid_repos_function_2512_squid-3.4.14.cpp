void
wordlistAddWl(wordlist ** list, wordlist * wl)
{
    while (*list)
        list = &(*list)->next;

    for (; wl; wl = wl->next, list = &(*list)->next) {
        *list = new wordlist();
        (*list)->key = xstrdup(wl->key);
        (*list)->next = NULL;
    }
}