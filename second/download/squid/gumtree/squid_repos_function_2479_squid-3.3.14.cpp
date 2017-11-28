wordlist *
wordlistDup(const wordlist * w)
{
    wordlist *D = NULL;

    while (NULL != w) {
        wordlistAdd(&D, w->key);
        w = w->next;
    }

    return D;
}