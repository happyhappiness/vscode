static apr_status_t asio_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    DBG_BUFF
    apr_status_t rv;
    apr_pollset_private_t *priv;

    DBG1(2, "entered, flags: %x\n", flags);

    priv = pollset->p = apr_palloc(p, sizeof(*priv));

    if (flags & APR_POLLSET_THREADSAFE) {
#if APR_HAS_THREADS
        if (rv = apr_thread_mutex_create(&(priv->ring_lock),
                                           APR_THREAD_MUTEX_DEFAULT,
                                           p) != APR_SUCCESS) {
            DBG1(1, "apr_thread_mutex_create returned %d\n", rv);
            pollset = NULL;
            return rv;
        }
        rv = msgget(IPC_PRIVATE, S_IWUSR+S_IRUSR); /* user r/w perms */
        if (rv < 0) {
#if DEBUG
            perror(__FUNCTION__ " msgget returned < 0 ");
#endif
            pollset = NULL;
            return rv;
        }

        DBG2(4, "pollset %p msgget was OK, rv=%d\n", pollset, rv);
        priv->msg_q = rv;
        priv->elems   = apr_hash_make(p);

        APR_RING_INIT(&priv->free_ring, asio_elem_t, link);
        APR_RING_INIT(&priv->prior_ready_ring, asio_elem_t, link);

#else  /* APR doesn't have threads but caller wants a threadsafe pollset */
        pollset = NULL;
        return APR_ENOTIMPL;
#endif

    } else {  /* APR_POLLSET_THREADSAFE not set, i.e. no async i/o,
               * init fields only needed in old style pollset
               */

        priv->pollset = apr_palloc(p, size * sizeof(struct pollfd));
        priv->query_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

        if ((!priv->pollset) || (!priv->query_set)) {
            return APR_ENOMEM;
        }
    }

    pollset->nelts   = 0;
    pollset->flags   = flags;
    pollset->pool    = p;
    priv->size    = size;
    priv->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));
    if (!priv->result_set) {
        return APR_ENOMEM;
    }

    DBG2(2, "exiting, pollset: %p, type: %s\n",
             pollset,
             flags & APR_POLLSET_THREADSAFE ? "async" : "POSIX");


    return APR_SUCCESS;

}