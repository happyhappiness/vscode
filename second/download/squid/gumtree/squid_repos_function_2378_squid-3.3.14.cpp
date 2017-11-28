void
ipcache_purgelru(void *voidnotused)
{
    dlink_node *m;
    dlink_node *prev = NULL;
    ipcache_entry *i;
    int removed = 0;
    eventAdd("ipcache_purgelru", ipcache_purgelru, NULL, 10.0, 1);

    for (m = lru_list.tail; m; m = prev) {
        if (ipcacheCount() < ipcache_low)
            break;

        prev = m->prev;

        i = (ipcache_entry *)m->data;

        if (i->locks != 0)
            continue;

        ipcacheRelease(i);

        ++removed;
    }

    debugs(14, 9, "ipcache_purgelru: removed " << removed << " entries");
}