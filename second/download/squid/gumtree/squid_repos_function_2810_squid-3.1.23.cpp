char *
CacheManager::PasswdGet(cachemgr_passwd * a, const char *action)
{
    wordlist *w;

    while (a != NULL) {
        for (w = a->actions; w != NULL; w = w->next) {
            if (0 == strcmp(w->key, action))
                return a->passwd;

            if (0 == strcmp(w->key, "all"))
                return a->passwd;
        }

        a = a->next;
    }

    return NULL;
}