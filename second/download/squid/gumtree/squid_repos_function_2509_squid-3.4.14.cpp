void
wordlistDestroy(wordlist ** list)
{
    wordlist *w = NULL;

    while ((w = *list) != NULL) {
        *list = w->next;
        safe_free(w->key);
        delete w;
    }

    *list = NULL;
}