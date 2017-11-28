static void
purge_entries_fromhosts(void)
{
    dlink_node *m = lru_list.head;
    ipcache_entry *i = NULL, *t;

    while (m) {
        if (i != NULL) {    /* need to delay deletion */
            ipcacheRelease(i);  /* we just override locks */
            i = NULL;
        }

        t = (ipcache_entry*)m->data;

        if (t->flags.fromhosts)
            i = t;

        m = m->next;
    }

    if (i != NULL)
        ipcacheRelease(i);
}