int h2_proxy_iq_empty(h2_proxy_iqueue *q)
{
    return q->nelts == 0;
}