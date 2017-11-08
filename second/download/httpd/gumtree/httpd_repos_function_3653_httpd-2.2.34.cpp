static APR_INLINE apr_skiplistnode *skiplist_qpop(apr_skiplist_q *q)
{
    return (q->pos > 0) ? q->data[--q->pos] : NULL;
}