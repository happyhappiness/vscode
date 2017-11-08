static int skiplisti_find_compare(apr_skiplist *sl, void *data,
                           apr_skiplistnode **ret,
                           apr_skiplist_compare comp)
{
    apr_skiplistnode *m = NULL;
    int count = 0;
    m = sl->top;
    while (m) {
        int compared;
        compared = (m->next) ? comp(data, m->next->data) : -1;
        if (compared == 0) {
            m = m->next;
            while (m->down) {
                m = m->down;
            }
            *ret = m;
            return count;
        }
        if ((m->next == NULL) || (compared < 0)) {
            m = m->down;
            count++;
        }
        else {
            m = m->next;
            count++;
        }
    }
    *ret = NULL;
    return count;
}