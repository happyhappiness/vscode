static int skiplisti_remove(apr_skiplist *sl, apr_skiplistnode *m, apr_skiplist_freefunc myfree)
{
    apr_skiplistnode *p;
    if (!m) {
        return 0;
    }
    if (m->nextindex) {
        skiplisti_remove(m->nextindex->sl, m->nextindex, NULL);
    }
    while (m->up) {
        m = m->up;
    }
    while (m) {
        p = m;
        p->prev->next = p->next;/* take me out of the list */
        if (p->next) {
            p->next->prev = p->prev;    /* take me out of the list */
        }
        m = m->down;
        /* This only frees the actual data in the bottom one */
        if (!m && myfree && p->data) {
            myfree(p->data);
        }
        skiplist_free_node(sl, p);
    }
    sl->size--;
    while (sl->top && sl->top->next == NULL) {
        /* While the row is empty and we are not on the bottom row */
        p = sl->top;
        sl->top = sl->top->down;/* Move top down one */
        if (sl->top) {
            sl->top->up = NULL; /* Make it think its the top */
        }
        skiplist_free_node(sl, p);
        sl->height--;
    }
    if (!sl->top) {
        sl->bottom = sl->bottomend = NULL;
        sl->topend = NULL;
    }
    return skiplist_height(sl);
}