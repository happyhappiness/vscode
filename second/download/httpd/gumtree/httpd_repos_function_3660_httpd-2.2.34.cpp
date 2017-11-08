static int skiplisti_find_compare(apr_skiplist *sl, void *data,
                           apr_skiplistnode **ret,
                           apr_skiplist_compare comp)
{
    int count = 0;
    apr_skiplistnode *m;
    m = sl->top;
    while (m) {
        if (m->next) {
            int compared = comp(data, m->next->data);
            if (compared == 0) {
                m = m->next;
                while (m->down) {
                    m = m->down;
                }
                *ret = m;
                return count;
            }
            if (compared > 0) {
                m = m->next;
                count++;
                continue;
            }
        }
        m = m->down;
        count++;
    }
    *ret = NULL;
    return count;
}