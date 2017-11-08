static APR_INLINE void skiplist_qclear(apr_skiplist_q *q)
{
    q->pos = 0;
}