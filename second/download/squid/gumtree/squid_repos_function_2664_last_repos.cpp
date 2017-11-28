void
fqdncache_purgelru(void *)
{
    dlink_node *m;
    dlink_node *prev = NULL;
    fqdncache_entry *f;
    int removed = 0;
    eventAdd("fqdncache_purgelru", fqdncache_purgelru, NULL, 10.0, 1);

    for (m = lru_list.tail; m; m = prev) {
        if (fqdncacheCount() < fqdncache_low)
            break;

        prev = m->prev;

        f = (fqdncache_entry *)m->data;

        if (f->locks != 0)
            continue;

        fqdncacheRelease(f);

        ++removed;
    }

    debugs(35, 9, "fqdncache_purgelru: removed " << removed << " entries");
}