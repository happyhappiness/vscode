char *
CacheManager::PasswdGet(Mgr::ActionPasswordList * a, const char *action)
{
    while (a) {
        for (auto &w : a->actions) {
            if (w.cmp(action) == 0)
                return a->passwd;

            static const SBuf allAction("all");
            if (w == allAction)
                return a->passwd;
        }

        a = a->next;
    }

    return NULL;
}