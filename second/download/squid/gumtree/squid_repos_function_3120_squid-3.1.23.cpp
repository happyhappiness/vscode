static void
purge_entries_fromhosts(void)
{
    dlink_node *m = lru_list.head;
    fqdncache_entry *i = NULL;
    fqdncache_entry *t;

    while (m) {
        if (i != NULL) {	/* need to delay deletion */
            fqdncacheRelease(i);	/* we just override locks */
            i = NULL;
        }

        t = (fqdncache_entry *)m->data;

        if (t->flags.fromhosts)
            i = t;

        m = m->next;
    }

    if (i != NULL)
        fqdncacheRelease(i);
}