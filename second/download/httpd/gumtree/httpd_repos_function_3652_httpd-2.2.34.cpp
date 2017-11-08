static apr_status_t skiplist_qpush(apr_skiplist_q *q, apr_skiplistnode *m)
{
    if (q->pos >= q->size) {
        apr_skiplistnode **data;
        size_t size = (q->pos) ? q->pos * 2 : 32;
        if (q->p) {
            data = apr_palloc(q->p, size * sizeof(*data));
            if (data) {
                memcpy(data, q->data, q->pos * sizeof(*data));
            }
        }
        else {
            data = realloc(q->data, size * sizeof(*data));
        }
        if (!data) {
            return APR_ENOMEM;
        }
        q->data = data;
        q->size = size;
    }
    q->data[q->pos++] = m;
    return APR_SUCCESS;
}