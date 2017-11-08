static struct waiter_t *make_waiter(apr_pool_t *pool)
{
    struct waiter_t *w = (struct waiter_t*)
                       apr_palloc(pool, sizeof(struct waiter_t));
    if (w == NULL)
        return NULL;
      
    w->sem  = create_sem(0, "apr conditional waiter");
    if (w->sem < 0)
        return NULL;

    APR_RING_ELEM_INIT(w, link);
    
    return w;
}