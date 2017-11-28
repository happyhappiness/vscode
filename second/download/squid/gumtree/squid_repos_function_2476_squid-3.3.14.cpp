void
wordlistJoin(wordlist ** list, wordlist ** wl)
{
    while (*list)
        list = &(*list)->next;

    *list = *wl;

    *wl = NULL;
}