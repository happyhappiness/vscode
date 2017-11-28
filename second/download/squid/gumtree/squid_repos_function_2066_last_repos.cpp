const char *
wordlistAdd(wordlist ** list, const char *key)
{
    while (*list)
        list = &(*list)->next;

    *list = new wordlist(key);
    return (*list)->key;
}