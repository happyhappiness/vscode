static void
dump_cachemgrpasswd(StoreEntry * entry, const char *name, Mgr::ActionPasswordList * list)
{
    while (list) {
        if (strcmp(list->passwd, "none") && strcmp(list->passwd, "disable"))
            storeAppendPrintf(entry, "%s XXXXXXXXXX", name);
        else
            storeAppendPrintf(entry, "%s %s", name, list->passwd);

        for (auto w : list->actions)
            entry->appendf(" " SQUIDSBUFPH, SQUIDSBUFPRINT(w));

        storeAppendPrintf(entry, "\n");
        list = list->next;
    }
}