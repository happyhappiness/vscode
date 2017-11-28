const char *
wordlistAdd(wordlist ** list, const char *key)
{
    while (*list)
        list = &(*list)->next;

    *list = new wordlist;

    (*list)->key = xstrdup(key);

    (*list)->next = NULL;

    return (*list)->key;
}